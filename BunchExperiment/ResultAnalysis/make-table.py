import sys
data0='''
'''

def parse(data0):
    data=[l for l in data0.split('\n') if len(l)>1]
    data2=[]
    i=-1
    for v in data:
        if v[0] == 'x': #not in '0123456789':
            data2.append([])
            i+=1
        else:
            data2[i].append(v)
    ns=[len(v) for v in data2]
    if max(ns) != min(ns):
        print('number of items does not match: '+str(ns), sys.stderr)
        exit(2)
    return data2

def write(data2, fout):
    n=len(data2[0])
    m=len(data2)
    for j in range(n):
        for i in range(m-1):
            fout.write(data2[i][j]+'\t')
        fout.write(data2[-1][j])
        fout.write("\n")

def main(infile, outfile=None):
    fin=open(infile)
    data0=fin.read()
    fin.close()
    data2=parse(data0)
    if outfile:
        fout=open(outfile, 'w')
    else:
        fout=sys.stdout
    write(data2, fout)
    if outfile:
        fout.close()

def fun(data, fn):
    fout=open(fn,'w')
    write(parse(data), fout)
    fout.close()

if __name__ == '__main__':
    argc=len(sys.argv)
    if argc < 2:
        print('Make several serialized multiple lists into a table. Each different list is separated by a line starting with "x"')
        print('Usage: <infile-name> [outfile-name]')
        exit(1)
    infile=sys.argv[1]
    outfile=sys.argv[2] if argc > 2 else None
    main(infile, outfile)
    
