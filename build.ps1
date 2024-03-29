Set-Location -Path "./syntax_analyzer"
& mingw32-make all

Set-Location -Path "../lexical_analyzer"
& mingw32-make all

Set-Location -Path ".."
& mingw32-make all