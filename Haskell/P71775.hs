-- preguntar al profe
countIf :: (Int -> Bool) -> [Int] -> Int

countIf f l = length (filter f l) 

pam :: [Int] -> [Int -> Int] -> [[Int]] 

pam l funcions =  [map f l| f <- funcions]

pam2 :: [Int] -> [Int -> Int] -> [[Int]]

pam2 l funcions = [[f numero| f <- funcions]| numero <- l]


filterFoldl :: (Int -> Bool) -> (Int -> Int -> Int) -> Int -> [Int] -> Int

filterFoldl  f_filter f_foldl v_init l = foldl f_foldl v_init (funcio_filter f_filter l)


funcio_filter :: (Int -> Bool) -> [Int] -> [Int]

funcio_filter f l = [x | x <- l, f x]



insert :: (Int -> Int -> Bool) -> [Int] -> Int -> [Int]

insert f l number_to_insert = [x| x<-l,  not (f number_to_insert x)] ++ [number_to_insert] ++ [x| x<-l, f number_to_insert x]




insertionSort :: (Int -> Int -> Bool) -> [Int] -> [Int]

insertionSort f [] = [] 
insertionSort f (x:xs) = insert f (insertionSort f xs) x




 



