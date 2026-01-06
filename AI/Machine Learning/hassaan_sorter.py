import os
import glob
import re
import shutil
import subprocess
import platform
import hashlib

VALID_MONTHS = ["JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"]
REQUIRED_SECTIONS = [
    "CC", "C0", "C1", "CE", "CN", "EC", "EE", "N1", "N2", "S1", "S2",
    "T1", "T2", "V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8",
    "X1", "X2", "X3", "X4", "X5", "X6", "X7"
]

def read_file(file_path):
    try:
        with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
            return f.read()
    except Exception as e:
        print(f"Error reading {file_path}: {str(e)}")
        return None

def get_dataset_hash(dataset):
    return hashlib.md5(dataset.encode('utf-8')).hexdigest()

def extract_datasets(text):
    pattern = r"(.*?CRUISE PERFORMANCE REPORT.*?\n+.*?X7[^\n]*\n)(?=(.*?CRUISE PERFORMANCE REPORT|\Z))"
    datasets = re.findall(pattern, text, re.DOTALL | re.MULTILINE)
    return [ds[0].strip() for ds in datasets if all(sec in ds[0] for sec in REQUIRED_SECTIONS) and re.match(r"X7\s", ds[0].splitlines()[-1].strip())]

def parse_cc_line(line):
    parts = line.strip().split()
    if len(parts) < 3 or parts[0].upper() != "CC":
        return None
    code = parts[1]
    m = re.match(r'^(?:[A-Z]{2}-)?([A-Z0-9]{3})$', code, re.I)
    return m.group(1).lower() if m else None

def unzip_files(directory):
    seven_zip_path = r"C:\Program Files\7-Zip\7z.exe" if platform.system() == "Windows" else "7z"
    try:
        subprocess.run([seven_zip_path, "--help"], capture_output=True, text=True, check=True)
    except (subprocess.CalledProcessError, FileNotFoundError):
        print(f"Error: 7-Zip not found at {seven_zip_path}. Please install 7-Zip.")
        return
    archive_extensions = ('.rar', '.zip', '.7z', '.tar', '.tar.gz', '.tgz', '.tar.bz2', '.tbz')
    for root, _, files in os.walk(directory):
        for file in files:
            if file.lower().endswith(archive_extensions):
                archive_path = os.path.join(root, file)
                print(f"Extracting: {archive_path}")
                try:
                    subprocess.run([seven_zip_path, "x", archive_path, f"-o{root}", "-y"], capture_output=True, text=True, check=True)
                    os.remove(archive_path)
                    print(f"Deleted: {archive_path}")
                except subprocess.CalledProcessError as e:
                    print(f"Error extracting {archive_path}: {e.stderr}")

def process_msg_dat_and_report02(directory):
    seen_hashes = set()
    for root, dirs, files in os.walk(directory):
        # Convert MSG.dat to MSG.txt
        if "MSG.dat" in files:
            dat_path = os.path.join(root, "MSG.dat")
            txt_path = os.path.join(root, "MSG.txt")
            try:
                shutil.copyfile(dat_path, txt_path)
                os.remove(dat_path)
                print(f"Converted {dat_path} to {txt_path}")
            except Exception as e:
                print(f"Error processing {dat_path}: {str(e)}")
        # Process REPORT02 folders
        if "REPORT02" in dirs:
            rpt = os.path.join(root, "REPORT02")
            for txt in glob.glob(os.path.join(rpt, "*.txt")):
                text = read_file(txt)
                if not text: continue
                for ds in extract_datasets(text):
                    ds_hash = get_dataset_hash(ds)
                    if ds_hash in seen_hashes:
                        continue
                    seen_hashes.add(ds_hash)
                    for ln in ds.splitlines():
                        if ln.strip().upper().startswith("CC"):
                            sfx = parse_cc_line(ln)
                            if sfx:
                                out = os.path.join(directory, f"{sfx}.txt")
                                with open(out, "a", encoding="utf-8") as o:
                                    o.write(ds + "\n\n")
                            break
            print(f"Processed REPORT02 in {rpt}")

def process_msg_txt_files(directory):
    seen_hashes = set()
    for file in glob.glob(os.path.join(directory, "**/*.[tT][xX][tT]"), recursive=True):
        if os.path.basename(file).lower() != "msg.txt":
            continue
        content = read_file(file)
        if not content:
            continue
        datasets = extract_datasets(content)
        base, _ = os.path.splitext(file)
        clean_path = f"{base}_clean.txt"
        with open(clean_path, "w", encoding="utf-8") as f:
            f.write("\n\n".join(datasets))
        print(f"Processed {file} into {clean_path}")
        # Process clean datasets
        for ds in datasets:
            ds_hash = get_dataset_hash(ds)
            if ds_hash in seen_hashes:
                continue
            seen_hashes.add(ds_hash)
            for ln in ds.splitlines():
                if ln.strip().upper().startswith("CC"):
                    sfx = parse_cc_line(ln)
                    if sfx:
                        out = os.path.join(directory, f"{sfx}.txt")
                        with open(out, "a", encoding="utf-8") as o:
                            o.write(ds + "\n\n")
                    break

def process_flight_files(directory, month):
    script_file = os.path.basename(__file__)
    folders = {
        'A321-211': ['bmm', 'bmn', 'bmo', 'bmp', 'bmw'],
        'A320-214': ['eda', 'edg', 'edh', 'edu', 'edv'],
        'A321-251 NX': ['boe', 'bod']
    }
    # Create destination folders
    for folder in folders:
        os.makedirs(os.path.join(directory, folder), exist_ok=True)
    # Process flight files for the specified month
    seen_hashes = set()
    for file_path in glob.glob(os.path.join(directory, "[a-zA-Z][a-zA-Z][a-zA-Z].txt")):
        content = read_file(file_path)
        if not content:
            continue
        valid_datasets = []
        for ds in extract_datasets(content):
            ds_hash = get_dataset_hash(ds)
            if ds_hash in seen_hashes:
                continue
            seen_hashes.add(ds_hash)
            for line in ds.splitlines():
                if line.startswith("CC") and len(line.split()) >= 3 and line.split()[2][:3].upper() == month.upper():
                    valid_datasets.append(ds)
                    break
        with open(file_path, "w", encoding="utf-8") as f:
            f.write("\n\n".join(valid_datasets))
        print(f"Processed {file_path} for month {month}")
        # Move to appropriate folder
        file_name = os.path.basename(file_path).lower()
        file_code = file_name[:3]
        for folder, codes in folders.items():
            if file_code in codes:
                dest_path = os.path.join(directory, folder, file_name)
                try:
                    shutil.move(file_path, dest_path)
                    print(f"Moved {file_name} to {folder}")
                except Exception as e:
                    print(f"Error moving {file_name} to {folder}: {str(e)}")
    # Clean up
    for entry in os.listdir(directory):
        entry_path = os.path.join(directory, entry)
        if os.path.isfile(entry_path) and entry != script_file:
            os.remove(entry_path)
            print(f"Deleted file: {entry_path}")
        elif os.path.isdir(entry_path) and entry not in folders:
            shutil.rmtree(entry_path)
            print(f"Deleted folder: {entry_path}")

def main():
    directory = os.getcwd()
    print(f"Starting processing in: {directory}")
    unzip_files(directory)
    process_msg_dat_and_report02(directory)
    process_msg_txt_files(directory)
    while True:
        month = input("Enter the month abbreviation (e.g., JAN/jan, MAY/may): ").strip().upper()
        if month in VALID_MONTHS:
            break
        print("Invalid month abbreviation. Please try again.")
    process_flight_files(directory, month)
    print("Processing complete.")

if __name__ == "__main__":
    main()