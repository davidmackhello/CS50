from flask import Flask, redirect, render_template, request, url_for

import os
import sys

import helpers
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, 100)

    # handle get_user_timeline errors
    if tweets == None:
        return redirect(url_for("index"))

    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)

    # counts for sentiment categories
    pos_count, neg_count, neut_count = 0, 0, 0

    # score and assign sentiment category to each tweet
    for tweet in tweets:
        score = analyzer.analyze(tweet)
        if score > 0.0:
            pos_count += 1
        elif score < 0.0:
            neg_count += 1
        else:
            neut_count += 1

    whole = pos_count + neg_count + neut_count
    positive, negative, neutral = (pos_count / whole), (neg_count / whole), (neut_count / whole)

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)