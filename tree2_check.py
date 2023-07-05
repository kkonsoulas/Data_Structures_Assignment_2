
class Node:
  def __init__(self, value, parent = None, left=None, right = None):
    self.value = value
    self.parent = parent
    self.left = left
    self.right = right
    
  def get_height(self):
    if self == None:
      return 0
    left_height = -1
    right_height = -1
    if self.left != None:
      left_height = self.left.get_height()
    if self.right != None:
      right_height = self.right.get_height()
    if left_height > right_height:
      return left_height + 1
    else:
      return right_height + 1
  
  def find_node(self, value):
    if self == None:
      return none
    if value < self.value:
      if self.left == None:
        return self
      else:
        return self.left.find_node(value)
    elif value > self.value:
      if self.right == None:
        return self
      else:
        return self.right.find_node(value)
    else:
      return self
  
  def print_preorder(self):
    print(self.value, end = " ")
    if self.left != None:
      self.left.print_preorder()
    if self.right != None:
      self.right.print_preorder()
    
class BinTree:

  def __init__(self):
    self.root = None
    self.size = 0
    
  def find_node(self, value):
    if self.size == 0:
      return None
    return self.root.find_node(value)
    
  def add(self, value):
    curr = self.root;
    if self.size == 0:
      node = Node(value)
      self.root = node
      self.size = 1;
      return True
    found = self.find_node(value)
    if found != None and found.value != value:
      node = Node(value, found)
      self.size += 1
      if value < found.value:
        found.left = node
      else:
        found.right = node
          
  def get_height(self):
    return self.root.get_height()
    
  def print_preorder(self):
    self.root.print_preorder()
    print("")
    

'''number = int(input())
while number >= 0:
  tree.add(number)
  tree.print_preorder()
  number = int(input()) '''
 
import math
import sys

def main():
  tree = BinTree()
  #print("sys.argv[1]:", sys.argv[1])
  with open(sys.argv[1], 'r') as reader:
    for line in reader:
      tokens = line.split()
      for token in tokens:
        #token = int(token)
        tree.add(int(token))
  
  print("Tree size:", tree.size, end=", ")  
  print("floor(log_2(",tree.size,")):", math.floor(math.log(tree.size, 2)))
  print("Actual tree height:", tree.get_height())
  
  if int(math.floor(math.log(tree.size, 2))) >= tree.get_height():
    print("TREE HEIGHT IS ACCEPTABLE")
    sys.exit(0)
  else:
    print("TREE HEIGHT IS NOT ACCEPTABLE")
    sys.exit(100)


if __name__ == "__main__":
    main()
