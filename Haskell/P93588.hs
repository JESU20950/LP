myMap :: (a -> b) -> [a] -> [b] 

myMap f l = [f x | x <- l]


myFilter :: (a-> Bool) -> [a] -> [a]

myFilter f l = [x | x <- l, f x]

myZipWith:: (a -> b -> c) -> [a] -> [b] -> [c] 
 
myZipWith f l1 l2 = [f (primer par) (segon par)| par <- (zip l1 l2)]

primer :: (a,b) -> a

primer (x,_) = x  

segon :: (a,b) -> b
segon (_,y) = y 

thingify :: [Int] -> [Int] -> [(Int, Int)]
thingify l1 l2 = [(x,y) | x<- l1 , y<- l2, mod x y == 0 ]

factors :: Int -> [Int]

factors x = [y| y <- [1 .. x], mod x y == 0]








