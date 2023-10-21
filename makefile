build:
	del /Q app.exe
	gcc.exe app.c MinPopVote.c -o app.exe

run:
	app.exe

run_quiet:
	app.exe -q

valgrind:
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes app.exe

run_fast:
	app.exe -f

run_fastAndQuiet:
	app.exe -f -q

run_year:
	app.exe -y

built_test:
	del /Q test.exe
	gcc.exe test.c MinPopVote.c -o test.exe

run_test:
	test.exe
