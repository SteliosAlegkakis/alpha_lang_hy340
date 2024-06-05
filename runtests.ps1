param(
    [string]$folder
)

$testFilesDirectory = $folder
$programPath = "./alphac.exe"

# Get the list of testfiles in the directory
$testFiles = Get-ChildItem -Path $testFilesDirectory -Filter "*.a"

# Loop through each testfile and run the program
foreach ($testFile in $testFiles) {
    Write-Host "`nRunning test file: $($testFile.Name)"
    & $programPath $testFile.FullName
    Write-Host ""
}
