from subprocess import check_output


for size in range(100, 20001, 100):
    with open('results.csv', 'a+') as output:
        time = check_output(['./yahtzee', f'{size}']).decode()
        output.write(f'{size}, {time}')
