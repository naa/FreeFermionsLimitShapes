import matplotlib.pyplot as plt
import sys, getopt
import numpy as np

def draw_horiz_tile(x,y,n,color='gray'):
    plt.fill([x,x+2/n,x+2/n,x,x],[y,y,y+1/n,y+1/n,y],color,edgecolor='black')

def draw_vert_tile(x,y,n,color='gray'):
    plt.fill([x,x+1/n,x+1/n,x,x],[y,y,y+2/n,y+2/n,y],color,edgecolor='black')

def draw_column_path(x,y,col,n,k,color1='gray',color2='blue'):
    for i in range(k):
        if i in col:
            draw_vert_tile(x,y,n,color=color1)
            x=x+1/n
            y=y+1/n
        else:
            draw_horiz_tile(x,y,n,color=color2)
            x=x+2/n

def draw_column_tiling(trtableau,n,k):
    x=0
    y=0
    for col in trtableau:
        draw_column_path(x,y,col,n,k)
        x+=1/n
        y-=1/n
    for i in range(k):
        draw_column_path(x,y,[],n,k-i)
        x+=1/n
        y-=1/n        

def draw_row_path(x,y,row,n,rownum,color1='yellow',color2='blue'):
    for i in range(rownum,n):
        for j in range(row.count(i)):
            draw_vert_tile(x-1/n,y,n,color=color1)
            x=x-1/n
            y=y+1/n                        
        draw_horiz_tile(x-2/n,y,n,color=color2)            
        x=x-2/n            
            
def draw_white_dominos(n,k):
    for i in range(1,n+k+1):
        for j in range(n+k):
            draw_horiz_tile((i+j)/n-1/(n),(i-j)/n,n,color='white')

        
def draw_row_tiling(tableau,n,k):
    x=2*(n+k)/n
    y=0
    for rownum,row in enumerate(tableau):
        draw_row_path(x,y,row,n,rownum)
        x-=1/n
        y-=1/n

def draw_diamond(trtableau,tableau,n,k):
    draw_white_dominos(n,k)
    draw_column_tiling(trtableau,n,k)
    draw_row_tiling(tableau,n,k)
    plt.plot([0-1/n,(n+k)/n,2*(n+k)/n+1/n,(n+k)/n,0-1/n],[0+1/n,-(n+k)/n,0+1/n,(n+k)/n+2/n,0+1/n])
    plt.plot([k/n-0.5/n,0.5/n+(n+k)/n+k/n],[k/n+1.5/n,-(n+k)/n+k/n+0.5/n],color='cyan')
  

def tableau_to_pattern(tableau,n):
    pre=[]
    res=[]
    for i in range(1,n+1):
        nl=[]
        pre=pre+[0]
        for j in range(i):
            if j<len(tableau):
                nl.append(tableau[j].count(i)+pre[j])
            else:
                nl.append(0)
        pre=nl
        res.append(nl)
    return list(reversed(res))

def reverse_pattern(pat,n,k):
    rpat=list(reversed(pat))
    r=[]
    for i in range(n):
        r.append([])
        for j in range(i+1):
            r[i].append(k-rpat[i][i-j])
    return list(reversed(r))

def pattern_to_tableau(pat):
    revpt=reversed(pat)
    n=len(pat)
    pre=[]
    res=[]
    for i,l in enumerate(revpt):
        res.append([])
        pre=pre+[0]
        for j in range(i+1):
            res[j].extend([i+1]*(l[j]-pre[j]))
        pre=l
    return res

def king_tableau_to_gl_half_tableau(ktab):
    return [[abs(v)*2-(1+v//abs(v))//2 for v in row] for row in ktab]

def king_tableau_to_gl_pattern(ktab,n,k):
    gltab=king_tableau_to_gl_half_tableau(ktab)
    pat=tableau_to_pattern(gltab,n)
    return [[row[i]+k//2-row[-(i+1)] for i,v in enumerate(row)] for row in pat]


def king_tableau_to_gl_tableau(ktab,n,k):
    return pattern_to_tableau(king_tableau_to_gl_pattern(ktab,n,k))

from itertools import zip_longest
def transpose_tableau(tab):
    return [list(filter(None,i)) for i in zip_longest(*tab)]


def draw_down_lozenge(x,y,n,color='gray'):
    plt.fill([x,x+np.sqrt(3)/(2*n),x+np.sqrt(3)/(2*n),x,x],[y,y-1/(2*n),y+1/(2*n),y+1/n,y],color,edgecolor='black')

def draw_up_lozenge(x,y,n,color='gray'):
    plt.fill([x,x+np.sqrt(3)/(2*n),x+np.sqrt(3)/(2*n),x,x],[y,y+1/(2*n),y+3/(2*n),y+1/n,y],color,edgecolor='black')

def draw_horiz_lozenge(x,y,n,color='gray'):
    plt.fill([x,x+np.sqrt(3)/(2*n),x+np.sqrt(3)/(n),x+np.sqrt(3)/(2*n),x],[y,y-1/(2*n),y,y+1/(2*n),y],color,edgecolor='black')

    
#def draw_horiz_lozenge_tile(x,y,n,color='gray'):
#    plt.fill([x,x+2/n,x+2/n,x,x],[y,y,y+1/n,y+1/n,y],color,edgecolor='black')
#
#def draw_vert_lozenge_tile(x,y,n,color='gray'):
#    plt.fill([x,x+1/n,x+1/n,x,x],[y,y,y+2/n,y+2/n,y],color,edgecolor='black')
#
def draw_column_lozenge_path(x,y,col,n,k,color1='gray',color2='blue'):
    for i in range(k):
        if i in col:
#            draw_vert_tile(x,y,n,color=color1)
            draw_up_lozenge(x,y,n,color=color1)            
            x=x+np.sqrt(3)/(2*n)
            y=y+1/(2*n)
        else:
#            draw_horiz_tile(x,y,n,color=color2)
            draw_down_lozenge(x,y,n,color=color2)
            x=x+np.sqrt(3)/(2*n)
            y=y-1/(2*n)            

def draw_column_lozenge_tiling(trtableau,n,k):
    x=0
    y=1-1/n
    for col in trtableau:
        draw_column_lozenge_path(x,y,col,n,k)
        y-=1/n
    for i in range(n-len(trtableau)):
        draw_column_lozenge_path(x,y,[],n,k-i)
        y-=1/n        

def draw_row_lozenge_path(x,y,row,n,rownum,color1='gray',color2='white'):
    for i in range(rownum,n):
        for j in range(row.count(i)):
            draw_up_lozenge(x-np.sqrt(3)/(2*n),y-1/(2*n),n,color=color1)
            y=y+1/n                                    
#            draw_vert_tile(x-1/n,y,n,color=color1)
#            x=x-1/n
#            y=y+1/n                        
        draw_horiz_lozenge(x-np.sqrt(3)/n,y,n,color=color2)            
        x=x-np.sqrt(3)/(2*n)
        y=y+1/(2*n)
            
def draw_white_lozenges(n,k):
    for i in range(1,n+k+1):
        for j in range(n+k):
            draw_horiz_lozenge_tile((i+j)/n-1/(n),(i-j)/n,n,color='white')

        
def draw_row_lozenge_tiling(tableau,n,k):
    x=np.sqrt(3)*(n+k)/(2*n)
    y=1/2-k/(2*n)
    for rownum,row in enumerate(tableau):
        draw_row_lozenge_path(x,y,row,n,rownum)
        x-=np.sqrt(3)/(2*n)
        y-=1/(2*n)

def draw_lozenge_lattice(n,k,color='black'):
    for i in range(n):
        plt.fill([np.sqrt(3)*k/(2*n)+i*np.sqrt(3)/(2*n),
                  np.sqrt(3)*k/(2*n)+i*np.sqrt(3)/(2*n),
                  np.sqrt(3)*k/(2*n)+(i+1)*np.sqrt(3)/(2*n),
                  np.sqrt(3)*k/(2*n)+(i+1)*np.sqrt(3)/(2*n),
                  np.sqrt(3)*k/(2*n)+i*np.sqrt(3)/(2*n),],
                 [-k/(2*n)+i/(2*n),1+k/(2*n)-i/(2*n),
                  1+k/(2*n)-(i+1)/(2*n),
                  -k/(2*n)+(i+1)/(2*n),
                  -k/(2*n)+i/(2*n)],
                 color,edgecolor='black')        
    for i in range(n+k):
        plt.fill([np.sqrt(3)*k/(2*n),0 if i<n else (i-n)*np.sqrt(3)/(2*n)],[1+k/(2*n)-i/n,1-i/n if i<n else -(i-n)/(2*n)],color,edgecolor='black')
        plt.fill([np.sqrt(3)*k/(2*n), (k-i)*np.sqrt(3)/(2*n) if i<k else 0],[1+k/(2*n)-i/n,1+k/(2*n)-i/(2*n) if i<k else 1-(i-k)/n],color,edgecolor='black')        
        plt.fill([np.sqrt(3)*k/(2*n),(n+k)*np.sqrt(3)/(2*n) if i<k else (n+k)*np.sqrt(3)/(2*n)-(i-k)*np.sqrt(3)/(2*n)],
                 [1+k/(2*n)-i/n,k/(2*n)+1/2-i/n if i<k else 1/2-k/(2*n)-(i-k)/(2*n)],color,edgecolor='black')

#        plt.fill([np.sqrt(3)*k/(2*n), (n+k)*np.sqrt(3)/(2*n)-(n-i)*np.sqrt(3)/(2*n) if i<n else (n+k)*np.sqrt(3)/(2*n)],
#                 [1+k/(2*n)-i/n,1+k/(2*n)-i/(2*n) if i<n else k/(2*n)+1/2-(i-n)/n],color,edgecolor='black')        

def draw_black_left_triangles(n,k,color='black'):
    for i in range(n+k):
#        draw_horiz_lozenge(np.sqrt(3)*k/(2*n)-np.sqrt(3)/(2*n),1+k/(2*n)-i/n-1/(2*n),n,color=color)
        plt.fill([np.sqrt(3)*k/(2*n),np.sqrt(3)*k/(2*n)-np.sqrt(3)/(2*n),np.sqrt(3)*k/(2*n),np.sqrt(3)*k/(2*n)],
                 [1+k/(2*n)-i/n,1+k/(2*n)-i/n-1/(2*n),1+k/(2*n)-i/n-1/n,1+k/(2*n)-i/n],color=color)


def draw_black_right_triangles(trtableau,tableau,n,k,color='black'):
    for i in range(n):
        a=len(trtableau[i])+n-i if i<len(trtableau) else n-i
        plt.fill([np.sqrt(3)*k/(2*n),np.sqrt(3)*k/(2*n)+np.sqrt(3)/(2*n),np.sqrt(3)*k/(2*n),np.sqrt(3)*k/(2*n)],
                 [-k/(2*n)+a/n,-k/(2*n)+a/n-1/(2*n),-k/(2*n)+a/n-1/n,-k/(2*n)+a/n],color=color)
        
def draw_skew_lozenge_tiling(tableauP,tableauQ,n,k):
    trtableau=transpose_tableau(tableauP)
    if len(trtableau)<n:
        trtableau.extend([[] for i in range(n-len(trtableau))])
    tableau=[[s-1 for s in l] for l in tableauQ]
    if len(tableau)<n:
        tableau.extend([[] for i in range(n-len(tableau))])
    draw_lozenge_lattice(n,k,color='blue')
    draw_black_left_triangles(n,k)

    draw_row_lozenge_tiling(tableau,n,k)        
    draw_column_lozenge_tiling(trtableau,n,k)
    draw_black_right_triangles(trtableau, tableau,n,k)    
    plt.plot([0,0,np.sqrt(3)*k/(2*n),np.sqrt(3)*k/(2*n),0],[1,0,-k/(2*n),1+k/(2*n),1],color='cyan')
    plt.plot([np.sqrt(3)*k/(2*n),np.sqrt(3)*(n+k)/(2*n),np.sqrt(3)*(n+k)/(2*n),np.sqrt(3)*k/(2*n),np.sqrt(3)*k/(2*n)],[-k/(2*n),1/2-k/(2*n),1/2+k/(2*n),1+k/(2*n),-k/(2*n)],color='cyan')        
#    plt.plot([0-1/n,(n+k)/n,2*(n+k)/n+1/n,(n+k)/n,0-1/n],[0+1/n,-(n+k)/n,0+1/n,(n+k)/n+2/n,0+1/n])
    
def draw_diamond_tiling(tableauP,tableauQ,n,k):
    trtableau=transpose_tableau(tableauP)
    if len(trtableau)<n:
        trtableau.extend([[] for i in range(n-len(trtableau))])
    tableau=[[s-1 for s in l] for l in tableauQ]
    if len(tableau)<n:
        tableau.extend([[] for i in range(n-len(tableau))])
    
    draw_white_dominos(n,k)
    draw_column_tiling(trtableau,n,k)
    draw_row_tiling(tableau,n,k)
    plt.plot([0-1/n,(n+k)/n,2*(n+k)/n+1/n,(n+k)/n,0-1/n],[0+1/n,-(n+k)/n,0+1/n,(n+k)/n+2/n,0+1/n])


