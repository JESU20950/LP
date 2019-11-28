multEq :: Int -> Int -> [Int]

multEq x y = 1:(map (*y) (map (*x) (multEq x y)))

selectFirst :: [Int] -> [Int] -> [Int] -> [Int]

selectFirst [] l2 l3 = []
selectFirst l1 [] l2 = []
selectFirst (x:xs) l2 l3
	|(elem x l2) && ((position x l2) < (position x l3) || (not (elem x l3) )) = [x] ++ (selectFirst xs l2 l3)
	|otherwise = (selectFirst  xs l2 l3)

position :: Int -> [Int] -> Int

position x l = positionaux x l 0


positionaux :: Int -> [Int] -> Int -> Int

positionaux x [] i = i
positionaux x (x1:xs) i
	|x == x1 = i
	|otherwise = positionaux x xs (i+1)

myIterate :: (a -> a) -> a -> [a]


myIterate f x = (scanl (\_ y -> f y) x (myIterate f x))


type SymTab a = String -> Maybe a

empty :: SymTab a

empty = \x -> Nothing

get :: SymTab a -> String -> Maybe a

get t palabra = t palabra

set :: SymTab a -> String -> a -> SymTab a

set t palabra valor = \x -> 
    if palabra == x then 
        Just valor 
    else 
        get t x



data Expr a = Val a | Var String | Sum (Expr a) (Expr a) | Sub (Expr a) (Expr a) | Mul (Expr a) (Expr a) 
    deriving (Show)


eval :: (Num a) => SymTab a -> Expr a -> Maybe a



eval t (Val a) = Just a
eval t (Sum x y) = evaluar (+) t x y
eval t (Sub x y) = evaluar (-) t x y
eval t (Mul x y) = evaluar (*) t x y
eval t (Var x) = get t x

evaluar :: (Num a) => (a->a->a) -> SymTab a -> Expr a -> Expr a -> Maybe a

evaluar f t x y =
	do 
	r <- eval t x 
	s <- eval t y
	Just (f r s) 

	


