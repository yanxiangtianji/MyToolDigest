import sys
data0='''
'''

def parse(data0):
    data1=[l for l in data0.split('\n') if len(l)>1]
    data_avg=[]
    data_std=[]
    for l in data1:
        x=[float(v) for v in l.split('\t')]
        n=len(x)
        m1=sum(x)/n
        m2=sum(v**2 for v in x)/n
        data_avg.append(m1)
        data_std.append(m2-m1**2)
    return data_avg, data_std

def write(data_avg, data_std, fout):
    n=len(data_avg)
    for i in range(n):
        #fout.write(str(data_avg[i])+'\t'+str(data_std[i])+'\n')
        fout.write('%.9f\t%.9f\n' % (data_avg[i], data_std[i]))

def main(infile, outfile=None):
    fin=open(infile)
    data0=fin.read()
    fin.close()
    data_a, data_s=parse(data0)
    if outfile:
        fout=open(outfile, 'w')
    else:
        fout=sys.stdout
    write(data_a, data_s, fout)
    if outfile:
        fout.close()

if __name__ == '__main__':
    argc=len(sys.argv)
    if argc < 2:
    	print('Average each row of a table and output a table with two column representing their mean and standard derivation')
        print('Usage: <infile-name> [outfile-name]')
        exit(1)
    infile=sys.argv[1]
    outfile=sys.argv[2] if argc > 2 else None
    main(infile, outfile)
    
