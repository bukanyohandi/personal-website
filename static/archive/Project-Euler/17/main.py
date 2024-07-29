def number_to_words(n):
    if n == 0:
        return "zero"
    if n == 1000:
        return "one thousand"
    under_20 = ['','one','two','three','four','five','six','seven','eight','nine',
                'ten','eleven','twelve','thirteen','fourteen','fifteen','sixteen',
                'seventeen','eighteen','nineteen']
    tens = ['', '', 'twenty','thirty','forty','fifty','sixty','seventy','eighty','ninety']
    hundreds = ['','one hundred','two hundred','three hundred','four hundred','five hundred',
                'six hundred','seven hundred','eight hundred','nine hundred']
    result = []
    if n >= 100:
        result.append(hundreds[n // 100])
        n %= 100
        if n > 0:
            result.append("and")
    if n >= 20:
        result.append(tens[n // 10])
        n %= 10
    if n > 0:
        result.append(under_20[n])
    return ' '.join(result)
def count_letters(word):
    return len(word.replace(' ', '').replace('-', ''))
total_letters = 0
for i in range(1, 1001):
    words = number_to_words(i)
    total_letters += count_letters(words)
print(total_letters)
