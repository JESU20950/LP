data Expr = Val Int | Add Expr Expr | Sub Expr Expr | Mul Expr Expr | Div Expr Expr

eval1 :: Expr -> Int
eval1 (Add fe fd) = (+) (eval1 fe) (eval1 fd)
eval1 (Sub fe fd) = (-) (eval1 fe) (eval1 fd)
eval1 (Mul fe fd) = (*) (eval1 fe) (eval1 fd)
eval1 (Div fe fd) = div (eval1 fe) (eval1 fd)
eval1 (Val x) = x

eval2 :: Expr -> Maybe Int

eval2 (Val x) = Just x
eval2 (Add fe fd) = evalmonad (+) fe fd
eval2 (Sub fe fd) = evalmonad (-) fe fd
eval2 (Mul fe fd) = evalmonad (*) fe fd

eval2 (Div fe fd)
	= do
	a <- eval2 fe 
	b <- eval2 fd
	if (b == 0) then do Nothing
	else Just (div a b)

evalmonad :: (Int -> Int -> Int) -> Expr -> Expr-> Maybe Int
evalmonad f x y
	= do
	i <- eval2 x
	j <- eval2 y
	Just (f i j)



eval3 :: Expr -> Either String Int

eval3 (Val x) = Right x
eval3 (Add fe fd) = evalmonad3 (+) fe fd
eval3 (Sub fe fd) = evalmonad3 (-) fe fd
eval3 (Mul fe fd) = evalmonad3 (*) fe fd

eval3 (Div fe fd)
	= do
	a <- eval3 fe 
	b <- eval3 fd
	if (b == 0) then do Left "div0"
	else Right (div a b)

evalmonad3 :: (Int -> Int -> Int) -> Expr -> Expr-> Either String Int
evalmonad3 f x y
	= do
	i <- eval3 x
	j <- eval3 y
	Right (f i j)


