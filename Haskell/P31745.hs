 
flatten :: [[Int]] -> [Int]

flatten l = foldl (++) [] l


myLength :: String -> Int 

myLength l = foldl (\x _ -> x+1) 0 l


myReverse :: [Int] -> [Int]

myReverse l = foldl (\l x -> [x] ++ l) [] l

countIn :: [[Int]] -> Int -> [Int]

countIn l b = map (length . filter (b == )) l

firstWord :: String -> String

firstWord l = takeWhile (/= ' ')  (dropWhile (== ' ') l )


