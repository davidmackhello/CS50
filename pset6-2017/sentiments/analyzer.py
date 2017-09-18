import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""

        def setload(listfile):
            """Parse formatted word list file and return set containing all words"""
        
            # scan word file formatted with ; comments and single newline
            with open(listfile) as f:
                for line in f:
                    if line[0] != ';':
                        break
                return set(line.strip() for line in f)

        # load sets for pos and neg word lists
        self.posi_set = setload(positives)
        self.negi_set = setload(negatives)

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        # configure tokenizer for strings only
        if isinstance(text, str):
            tokenizer = nltk.tokenize.TweetTokenizer(preserve_case=False)
            tokens = tokenizer.tokenize(text)

            # score each word to determine set score
            score = 0
            for word in tokens:
                if word in self.posi_set:
                    score += 1
                if word in self.negi_set:
                    score -= 1
            return score

        # return None for errors
        else:
            return None