Write-Host "=== CFSolve bootstrap ==="

# Always run from repo root
$ROOT = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $ROOT

# 1. Clean old artifacts
Write-Host "Cleaning old artifacts..."
Remove-Item -Recurse -Force build, dist, *.egg-info -ErrorAction SilentlyContinue
Remove-Item -Recurse -Force .venv -ErrorAction SilentlyContinue

# 2. Create virtual environment
Write-Host "Creating virtual environment..."
python -m venv .venv
.\.venv\Scripts\Activate.ps1

# 3. Upgrade build tools
Write-Host "Upgrading pip tooling..."
python -m pip install --upgrade pip setuptools wheel cmake ninja

# 4. Install runtime + build deps
Write-Host "Installing Python dependencies..."
pip install pybind11 numpy

# 5. Build & install the project
Write-Host "Building and installing solver..."
pip install -v .

Write-Host ""
Write-Host "=== DONE ==="
Write-Host "To run:"
Write-Host "  .\.venv\Scripts\activate"
Write-Host "  python src\gui\main.py"