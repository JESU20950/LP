create :: Queue a

create = Queue [] [] 

push :: a -> Queue a -> Queue a

push element (Queue l l2) = (Queue l (element:l2) )


pop :: Queue a -> Queue a

pop (Queue [] []) = (Queue [] [])
pop (Queue [] l1) = (Queue (tail $ reverse l1) [])
pop (Queue l1 l2) = (Queue (tail l1) l2) 


top :: Queue a -> a

top (Queue [] l2) =  last l2
top (Queue (x:xs) _) = x

empty :: Queue a -> Bool
 
empty (Queue [] [] ) = True;
empty (Queue _ _) = False;

instance Eq a => Eq (Queue a) 
    where
        (Queue l1 l2) == (Queue l3 l4) = comparar (l1++reverse l2) (l3++reverse l4)
        
comparar :: Eq a => [a] -> [a] -> Bool

comparar [] [] = True
comparar [] _ = False
comparar _ [] = False
comparar (x:xs) (x2:xs2) = (x == x2) && (comparar xs xs2)

--P50086

data Queue a = Queue [a] [a]
	deriving (Show)
instance Functor Queue where
 fmap f (Queue l1 l2) = Queue (map f l1) (map f l2)


translation :: Num b => b -> Queue b -> Queue b 

translation x (Queue l1 l2) = Queue l1 (map (+x) l2)


instance Monad Queue  where
   return l1 l2 = Queue l1 l2  
   (Queue l1 l2) >>= f = Queue (map f l1) (map f l2)
    

--kfilter :: (p -> Bool) -> Queue p -> Queue p 
--kfilter f ([] []) = Queue [] []
--kfilter f (Queue l1 l2) =
  --  do
    --  return map f l1
      
    
