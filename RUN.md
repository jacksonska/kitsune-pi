# Using tshark to parse packets
## On RPi
```bash
sudo apt update
sudo apt install wireshark
```
## On personal machine
### Mac OS (w/homebrew)
```zsh
brew install --cask wireshark
```
### Windows (w/choco)
`choco install wireshark`

### Other options
https://tshark.dev/setup/install/

# Running Kitsune
## Setup Virtual Environment & Install the dependencies
```bash
python3 -m venv venv
source venv/bin/activate # (on MAC)
pip install -r requirements.txt
```
## Running example.py - Pre-recorded data
```bash
python3 example.py
```

## Run the live version of demo
```bash
python3 demo.py
``` 



