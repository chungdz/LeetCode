class Trie:
    def __init__(self):
        self.has_word = False
        self.children = {}
    
    def insert(self, word):
        curt = self
        for w in word:
            if w not in curt.children:
                curt.children[w] = Trie()
            curt = curt.children[w]
        curt.has_word = True
    
    def search_prefix(self, prefix):
        curt = self
        for w in prefix:
            if w in curt.children:
                curt = curt.children[w]
            else:
                return None
        return curt
    
    def has_word(self, word):
        if self.search_prefix(word) is not None:
            return True
    
    def find_child(self, c):
        if c in self.children:
            return self.children[c]
        else:
            return None
