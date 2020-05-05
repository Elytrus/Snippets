import subprocess as sub

if __name__ == '__main__':
    print('Installing required deps...')
    sub.run(['pip', 'install', 'toml', 'markdown'])
