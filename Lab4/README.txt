------------------------
Lab 4: Roman Numeral Conversion
CMPE 012 Spring 2019
Lee, Juan

-------------------------
Can you validly represent the decimal value 1098 with Roman numerals using only I, V, X, and C?
No because C only represents 100 and there can't be five Cs in a row. You need to use M to signify 1000 in Roman numeral. You also need to use L to signify 50 in Roman numeral for representing 98. It is doable but it would not be valid to do so. 

What was your approach for recognizing an invalid program argument?
I would first check if the values inserted were any of the characters used in Roman numeral so for example, v would be invalid while V is valid. Then I used the current and the next value compassions to figure out if the Roman numeral placements are valid. 

What did you learn in this lab?
I learn the rules of creating a Roman numeral value that follows all the valid rules of a Roman numeral. I learned about the address placements within the registers. I can manipulate which address a certain value would be stored. I also learned how to convert a decimal value to binary. 

Did you encounter any issues? Were there parts of this lab you found enjoyable?
I had severe problems with loading next next value of the Roman numeral. I ran into a problem where the address was overloaded and couldn't load the next next byte. When I assembled everything and ran it and it worked that was the most enjoyable part of this lab. 

How would you redesign this lab to make it better?
I would give clearer instructions in terms of what to do in sequence. I would also explain in class what bit masking is because it was essential in completing this lab. 

What resources did you use to complete this lab?
http://www.cs.uwm.edu/classes/cs315/Bacon/Lecture/HTML/ch05s03.html
https://chortle.ccsu.edu/AssemblyTutorial/Chapter-14/ass14_5.html
http://mathworld.wolfram.com/RomanNumerals.html

Did you work with anyone on the labs? Describe the level of collaboration.
I did not work with anyone on this lab. The only level of collaboration was asking questions to the TAs and they help me debug a lot of cases and gave me good explanations on the fundamentals of MIPS
