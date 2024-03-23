param(
    [string]$folder
)

$testFilesDirectory = "./testfiles/$folder"
$programPath = "./a.exe"

# Get the list of testfiles in the directory
$testFiles = Get-ChildItem -Path $testFilesDirectory -Filter "*.asc"

# Loop through each testfile and run the program
foreach ($testFile in $testFiles) {
    Write-Host "`nRunning test file: $($testFile.Name)"
    & $programPath $testFile.FullName
}
