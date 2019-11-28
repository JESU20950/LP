
myFoldl :: (a -> b -> a) -> a -> [b] -> a

myFoldl f valor_total [] = valor_total
myFoldl f valor_total (x:xs) = myFoldl f (f valor_total x) xs



myFoldr :: (a -> b -> b) -> b -> [a] -> b

myFoldr f valor_inicial [] = valor_inicial 
myFoldr f valor_inicial (x:xs) = f x (myFoldr f valor_inicial xs) 


myIterate :: (a -> a) -> a -> [a]

myIterate f x = [x] ++ myIterate f (f x)


myUntil :: (a -> Bool) -> (a -> a) -> a -> a

myUntil condicion f x 
	|not (condicion x) = myUntil condicion f (f x) 
	|otherwise = x

myMap :: (a-> b) -> [a] -> [b] 

myMap f l = [f x| x <- l]

myFilter :: (a-> Bool) -> [a] -> [a]

myFilter f l = [ x| x <- l, f x]


myAll :: (a-> Bool) -> [a] -> Bool

myAll f l = and (myMap f l)


myAny :: (a-> Bool) -> [a] -> Bool

myAny f l = or (myMap f l)

myZip :: [a] -> [b] -> [(a, b)]

myZip _ [] = []
myZip [] _ = []
myZip (x1:xs1) (x2:xs2) = [(x1,x2)] ++ (myZip xs1 xs2)

myZipWith :: (a->b->c) -> [a] -> [b] -> [c]

myZipWith f l1 l2 = [f (primer par) (segon par) | par <- myZip l1 l2]


primer :: (a,b) -> a 
primer (x,_) = x  
 
segon :: (a,b) -> b
segon (_,y) = y



























 















