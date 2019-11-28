
ones :: [Integer]

ones = repeat 1

nats :: [Integer]

nats = scanl (+) 0 ones

ints :: [Integer]

ints = [0] ++ intsrecursiu 1 

intsrecursiu :: Integer -> [Integer]

intsrecursiu i = [i,-i] ++ intsrecursiu (i+1)

triangulars :: [Integer]

triangulars =  tail (scanl (+) 0 nats)



factorials :: [Integer]

factorials = [1] ++ factorialaux 1 1

factorialaux :: Integer -> Integer -> [Integer]

factorialaux x i = (x*i):factorialaux (x*i) (i+1)

primes :: [Integer]

primes = garbell y
	where y =  (tail $ tail nats)


garbell :: [Integer] -> [Integer]

garbell (x:xs) = x:garbell [t| t <- xs , (mod t x) /= 0]


fibs :: [Integer]

fibs = fibsaux 0 1

fibsaux :: Integer -> Integer -> [Integer]

fibsaux x x2 = x:fibsaux x2 (x+x2)

hammings :: [Integer]

hammings = [1] ++ filter funcionfilter y
	where y =  (tail $ tail nats)

funcionfilter :: Integer -> Bool

funcionfilter x
	|x == 1 = True
	|mod x 2 == 0 = funcionfilter (div x 2)
	|mod x 3 == 0 = funcionfilter (div x 3)
	|mod x 5 == 0 = funcionfilter (div x 5)
	|otherwise = False


lookNsay :: [Integer] 

lookNsay = [1] ++ lookNsayaux 1

lookNsayaux :: Integer -> [Integer]

lookNsayaux x = n:lookNsayaux n
	where n = calcular x

calcular ::  Integer -> Integer

calcular 0 = 0
calcular x = (calcular y)*100 + i*10 + r
	where 
	r = mod x 10
	i = iterator x r
	y = div x (10 ^ i)

iterator :: Integer -> 	Integer -> Integer 

iterator x r
	|mod x 10 /= r = 0
	|otherwise = 1+(iterator (div x 10) r)


tartaglia :: [[Integer]]

	 

tartaglia = [[1]] ++ [[1,1]] ++ tartagliaux [1,1]


tartagliaux :: [Integer] -> [[Integer]]

tartagliaux l = [resultado] ++ tartagliaux resultado
	where 
	 resultado = [1]++(next_line l)

next_line :: [Integer] -> [Integer]

next_line [x] = [x]
next_line l = [(head l) + (head $ tail l)] ++ next_line (tail l)








