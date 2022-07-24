from itertools import count
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

import requests
def find():
    for j in range(1000):
        r=requests.get('http://192.168.137.20/')
        s=r.text
        c=""
        for i in range(12,len(s)):
            if(s[i]=='<'):
                break;
            c=c+s[i]
        c=float(c)
        return c
    




plt.style.use('Solarize_Light2')


xvals=[]
yvals=[]

index=count()

def animate(i):
    xvals.append(next(index))
    yvals.append(find())
    plt.cla()
    plt.xlabel("sensor")
    plt.ylabel("object distance")
    plt.plot(xvals,yvals,"r")

ani=FuncAnimation(plt.gcf(),animate,interval=50)
    


plt.tight_layout()
plt.show()
