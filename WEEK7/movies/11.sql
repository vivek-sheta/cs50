SELECT movies.title FROM movies,ratings 
WHERE movie_id 
IN (SELECT movie_id FROM stars WHERE person_id 
IN (SELECT id FROM people WHERE name = "Chadwick Boseman")) 
AND ratings.movie_id = movies.id 
ORDER BY ratings.rating desc 
limit 5;
