import qsolve;

buy = True;

def strategy(aDate):
    global buy
    if buy:
        qsolve.order("AAA", 5)
        buy = buy ^ True
    else:
        qsolve.order("AAA", -1)
        buy = buy ^ True
    

def init():
    return;
