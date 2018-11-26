from subprocess import check_output


with open('results.csv', 'a+') as output:
        for size in range(100, 10001, 100):
            time = check_output(['./yahtzee', f'{size}']).decode()
            output.write(f'{size}, {time}')
        output.write('\n')