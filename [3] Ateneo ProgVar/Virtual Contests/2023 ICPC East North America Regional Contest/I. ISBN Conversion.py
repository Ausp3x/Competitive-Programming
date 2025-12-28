# check if ISBN-10 is valid
# generate ISBN-13 and check if it is valid

def isValidISBN10(isbn10):
    l = len(isbn10)
    
    hyphen_idxs = []
    for i in range(l):
        if isbn10[i] == '-':
            hyphen_idxs.append(i)
    
    if len(hyphen_idxs) > 3 or len(isbn10) - len(hyphen_idxs) != 10:
        return False
    
    if len(hyphen_idxs) > 0:
        if hyphen_idxs[0] == 0 or hyphen_idxs[-1] == l - 1:
            return False
    
    if len(hyphen_idxs) == 3:
        if hyphen_idxs[-1] != l - 2:
            return False
    
    for i in range(len(hyphen_idxs) - 1):
        if hyphen_idxs[i] + 1 == hyphen_idxs[i + 1]:
            return False
    
    sanitized_isbn10 = ''
    for c in isbn10:
        if c == '-':
            continue
    
        sanitized_isbn10 += c
    
    ttl = 0
    for i in range(10):
        ttl += (10 - i) * (10 if sanitized_isbn10[i] == 'X' else int(sanitized_isbn10[i]))

    return ttl % 11 == 0

def generateValidISBN13(isbn10):
    isbn13 = '978-' + isbn10[:-1]
    
    sanitized_isbn13 = ''
    for c in isbn13:
        if c == 'X':
            print('invalid')
            return
            
        if c == '-':
            continue
        
        sanitized_isbn13 += c

    ttl = 0
    for i in range(12):
        ttl += (1 + 2 * (i % 2 == 1)) * int(sanitized_isbn13[i])
    
    ttl %= 10
    for i in range(10):
        if (ttl + i) % 10 == 0:
            isbn13 += str(i)
            
    print(isbn13)
    
    return

t = int(input())
while t > 0:
    isbn10 = input()
    
    if not isValidISBN10(isbn10):
        print('invalid')
        t -= 1
        continue

    generateValidISBN13(isbn10)
    
    t -= 1