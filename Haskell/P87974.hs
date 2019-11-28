isnomfemeni :: [Char] -> Bool

isnomfemeni [x] = (x == 'a' || x == 'A')
isnomfemeni (x:xs) = isnomfemeni xs

main = do
	x <- getLine
	if (isnomfemeni x) then do putStrLn "Hola maca!"
	else putStrLn "Hola maco!"
