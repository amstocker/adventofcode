open Printf

let read_file filename = 
  let ic = open_in filename in
  let n = in_channel_length ic in
  let b = String.create n in
  really_input ic b 0 n;
  close_in ic;
  (b)

let explode s =
  let rec exp i l =
    if i < 0 then l else exp (i - 1) (s.[i] :: l) in
  exp (String.length s - 1) []

let rec count_char lst chr =
  match lst with
  | [] -> 0
  | hd :: tl -> (count_char tl chr) + if hd = chr then 1 else 0

let () =
  let s = read_file Sys.argv.(1) in
  let l = explode s in
  
  (* Part 1 *)
  let up = count_char l '(' in
  let down = count_char l ')' in
  printf "char count: %d\n" (up-down)
