get_nom :: [Char] -> [Char]

get_nom t = takeWhile (/= ' ') t

get_massa:: [Char] -> Float

get_massa t =    read $ takeWhile (/= ' ') (dropWhile (== ' ') (dropWhile (/= ' ') t)) 


get_altura :: [Char] -> Float

get_altura t =  read $ takeWhile (/= ' ') (dropWhile (== ' ') (dropWhile (/= ' ') (dropWhile (== ' ') (dropWhile (/= ' ') t)))) 

interpretacio :: Float -> String

interpretacio imc
    |imc <18 = "magror"
    |imc >= 18 && imc <=25 = "corpulencia normal"
    |imc >= 25 && imc <=30 = "sobrepes"
    |imc >=30 && imc <= 40 = "obesitat"
    |otherwise = "obesitat morbida"
    
main = do
	line <- getLine
	if line /= "*" then do 
	let nom_persona = get_nom line
	let massa_persona = get_massa line
	let altura_persona = get_altura line	
	let imc = (/) massa_persona (altura_persona**2.0)
        putStrLn $ (nom_persona ++ ": " ++ (interpretacio imc))
	main 
	else return ()


