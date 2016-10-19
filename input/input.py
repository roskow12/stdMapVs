from random import randint

LOWEST_ID = 1
HIGHEST_ID = 45000

input_file = open("input.txt", 'w')

for x in range(1, 90000):
	input_file.write(str(randint(LOWEST_ID, HIGHEST_ID)) + "\n")

input_file.close()