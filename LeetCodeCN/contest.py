def isNStraightHand(hand, W):
    """
    :type hand: List[int]
    :type W: int
    :rtype: bool
    """
    hand.sort();
    if (len(hand) % W == 0):
      for i in range(int(len(hand) / W)):
        a = hand[0];
        for j in range(W):
          if (a in hand):
            hand.remove(a);
            a = a + 1;
          else:
            return False;
      return True;
    else:
      return False;

print(isNStraightHand(hand=[1,2,3,6,2,3,4,7,9], W=3));