class BIT:
    def __init__(self, leng):
        self.length = leng
        self.tree = [0] * (leng + 1)
        self.arr = [0] * (leng + 1)
        self.max_bit = 1
        while self.max_bit <= self.length: self.max_bit <<= 1

    def sum(self, x):
        ttl = 0
        
        while x > 0:
            ttl += self.tree[x]
            x -= x & -x
            
        return ttl

    def add(self, x, z):
        while x <= self.length:
            self.tree[x] += z
            x += x & -x

    def set(self, x, z):
        self.add(x, -arr[x] + z)
        arr[x] = z

    def search(self, x, first_index=False):
        if first_index: x -= 1
        index = 0
        total = 0
        curr_bit = self.max_bit
        while curr_bit > 0:
            alt = index | curr_bit
            if alt <= self.length and total + self.tree[alt] <= x:
                index = alt
                total += self.tree[alt]
            curr_bit >>= 1

        return index + 1 if first_index else index
        
    def __len__(self): return self.length
    def __str__(self): return str([self.sum(i) for i in range(1, self.length + 1)])

#Testing

bit = BIT(20)

bit.add(3, 10)
bit.add(4, 20)
bit.add(1, 3)
bit.add(14, 2000)
bit.add(12, 10)

print(bit)
print('3:', bit.sum(3), '10:', bit.sum(10), '20:', bit.sum(20))
print('search:', bit.search(33, True), 'search (not strict):', bit.search(33))
