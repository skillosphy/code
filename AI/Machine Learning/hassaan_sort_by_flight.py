import os
import glob
import re
import shutil
import subprocess
import platform
import hashlib

VALID_MONTHS = ["JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"]
REQUIRED_SECTIONS = [
    "CC", "C0", "C1", "CE", "CN", "EC", "EE",
    "N1", "N2", "S1", "S2", "T1", "T2",
    "V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8",
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

def unzip_initial_files(directory):
    seven_zip_path = r"C:\Program Files\7-Zip\7z.exe" if platform.system() == "Windows" else "7z"
    try:
        subprocess.run([seven_zip_path, "--help"], capture_output=True, text=True, check=True)
    except (subprocess.CalledProcessError, FileNotFoundError):
        print(f"Error: 7-Zip not found at {seven_zip_path}. Please install 7-Zip.")
        return
    zip_files = glob.glob(os.path.join(directory, "*.zip"))
    for zip_file in zip_files:
        print(f"Unzipping: {zip_file}")
        try:
            subprocess.run([seven_zip_path, "x", zip_file, f"-o{directory}", "-y"], capture_output=True, text=True, check=True)
            os.remove(zip_file)
            print(f"Deleted: {zip_file}")
        except subprocess.CalledProcessError as e:
            print(f"Error unzipping {zip_file}: {e.stderr}")

def script1_find_and_extract_archives(directory):
    def get_7zip_path():
        return r"C:\Program Files\7-Zip\7z.exe" if platform.system() == "Windows" else "7z"
    
    seven_zip_path = get_7zip_path()
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
                print(f"Processing archive: {archive_path}")
                try:
                    subprocess.run([seven_zip_path, "x", archive_path, f"-o{root}", "-y"], capture_output=True, text=True, check=True)
                    os.remove(archive_path)
                    print(f"Extracted and deleted: {archive_path}")
                except subprocess.CalledProcessError as e:
                    print(f"Error extracting {archive_path}: {e.stderr}")

def script2_convert_msg_dat_to_txt(directory):
    for root, _, files in os.walk(directory):
        for file in files:
            if file.lower() == "msg.dat":
                dat_path = os.path.join(root, file)
                txt_path = os.path.join(root, "MSG.txt")
                try:
                    shutil.copyfile(dat_path, txt_path)
                    os.remove(dat_path)
                    print(f"Converted {dat_path} to {txt_path} and deleted original")
                except Exception as e:
                    print(f"Error processing {dat_path}: {str(e)}")

def extract_datasets_regex(text):
    parts = re.split(r'(?mi)(?=^[ \t]*[A-Z0-9 \t]+PERFORMANCE REPORT)', text)
    return [p.strip() for p in parts
            if re.match(r'(?i)^[ \t]*[A-Z0-9 \t]+PERFORMANCE REPORT', p)]

def parse_cc_line(line):
    parts = line.strip().split()
    if len(parts) < 3 or parts[0].upper() != "CC":
        return None
    code = parts[1]
    m = re.match(r'^(?:[A-Z]{2}-)?([A-Z0-9]{3})$', code, re.I)
    return m.group(1).upper() if m else None

def script2_extract_report02(directory):
    seen_hashes = set()
    for root, dirs, _ in os.walk(directory):
        if "REPORT02" in dirs:
            rpt = os.path.join(root, "REPORT02")
            for txt in glob.glob(os.path.join(rpt, "*.txt")):
                text = read_file(txt)
                if not text: continue
                for ds in extract_datasets_regex(text):
                    if all(sec in ds for sec in REQUIRED_SECTIONS):
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

def script3_combine_merged_reports(directory):
    master_report_path = os.path.join(directory, "master_report.txt")
    files_to_merge = glob.glob(os.path.join(directory, "**/merged_report.txt"), recursive=True)
    if files_to_merge:
        try:
            with open(master_report_path, "w", encoding="utf-8") as outfile:
                for file_path in files_to_merge:
                    with open(file_path, "r", encoding="utf-8", errors="ignore") as infile:
                        outfile.write(infile.read() + "\n")
            print(f"Merged {len(files_to_merge)} files into {master_report_path}")
        except Exception as e:
            print(f"Error creating {master_report_path}: {str(e)}")

def script4_create_master_2(directory):
    def extract_complete_datasets(content):
        pattern = r"(.*?CRUISE PERFORMANCE REPORT.*?\n+.*?X7[^\n]*\n)(?=(.*?CRUISE PERFORMANCE REPORT|\Z))"
        datasets = re.findall(pattern, content, re.DOTALL | re.MULTILINE)
        required_sections = ["CC", "C0", "C1", "CE", "CN", "EC", "EE", "N1", "N2", "S1", "S2",
                             "T1", "T2", "V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8",
                             "X1", "X2", "X3", "X4", "X5", "X6", "X7"]
        valid_datasets = []
        for dataset in datasets:
            dataset_content = dataset[0].strip()
            if all(section in dataset_content for section in required_sections) and re.match(r"X7\s", dataset_content.splitlines()[-1].strip()):
                valid_datasets.append(dataset_content)
        return valid_datasets

    master_report_path = os.path.join(directory, "master_report.txt")
    master_2_path = os.path.join(directory, "master_2.txt")
    if os.path.isfile(master_report_path):
        content = read_file(master_report_path)
        if content:
            valid_datasets = extract_complete_datasets(content)
            try:
                with open(master_2_path, "w", encoding="utf-8") as f:
                    f.write("\n\n".join(valid_datasets) if valid_datasets else "")
                print(f"Created {master_2_path} with {len(valid_datasets)} datasets")
            except Exception as e:
                print(f"Error writing {master_2_path}: {str(e)}")

def script5_separate_flights_by_xxx(directory):
    def extract_complete_datasets(content):
        pattern = r"(.*?CRUISE PERFORMANCE REPORT.*?\n+.*?X7[^\n]*\n)(?=(.*?CRUISE PERFORMANCE REPORT|\Z))"
        datasets = re.findall(pattern, content, re.DOTALL | re.MULTILINE)
        required_sections = ["CC", "C0", "C1", "CE", "CN", "EC", "EE", "N1", "N2", "S1", "S2",
                             "T1", "T2", "V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8",
                             "X1", "X2", "X3", "X4", "X5", "X6", "X7"]
        valid_datasets = []
        seen_hashes = set()
        for dataset in datasets:
            dataset_content = dataset[0].strip()
            if all(section in dataset_content for section in required_sections) and re.match(r"X7\s", dataset_content.splitlines()[-1].strip()):
                ds_hash = get_dataset_hash(dataset_content)
                if ds_hash in seen_hashes:
                    continue
                seen_hashes.add(ds_hash)
                cc_match = re.search(r"CC\s+AP-([A-Z]{3})\b", dataset_content)
                if cc_match:
                    flight_code = cc_match.group(1).lower()
                    valid_datasets.append((flight_code, dataset_content))
        return valid_datasets

    master_2_path = os.path.join(directory, "master_2.txt")
    if os.path.isfile(master_2_path):
        content = read_file(master_2_path)
        if content:
            datasets = extract_complete_datasets(content)
            flight_datasets = {}
            for flight_code, dataset in datasets:
                flight_datasets.setdefault(flight_code, []).append(dataset)
            for flight_code, flight_data in flight_datasets.items():
                output_path = os.path.join(directory, f"{flight_code}.txt")
                try:
                    with open(output_path, "w", encoding="utf-8") as f:
                        f.write("\n\n".join(flight_data))
                    print(f"Wrote {len(flight_data)} datasets to {output_path}")
                except Exception as e:
                    print(f"Error writing {output_path}: {str(e)}")

def script6_process_msg_txt_files(directory):
    def find_last_x7_line(file_path):
        last_x7_line = 0
        with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
            for i, line in enumerate(f, 1):
                if line.rstrip().startswith("X7"):
                    last_x7_line = i
        return last_x7_line

    def extract_complete_datasets(file_path, last_x7_line):
        current_dataset = []
        datasets = []
        inside_dataset = False
        line_count = 0
        required_sections = ["CC", "C0", "C1", "CE", "CN", "EC", "EE", "N1", "N2", "S1", "S2",
                             "T1", "T2", "V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8",
                             "X1", "X2", "X3", "X4", "X5", "X6", "X7"]
        seen_hashes = set()
        with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
            for line in f:
                line_count += 1
                if line_count > last_x7_line:
                    break
                stripped_line = line.rstrip()
                if not inside_dataset and "CRUISE PERFORMANCE REPORT" in stripped_line:
                    inside_dataset = True
                    current_dataset.append(line)
                elif inside_dataset:
                    current_dataset.append(line)
                    if stripped_line.startswith("X7"):
                        dataset = "".join(current_dataset)
                        ds_hash = get_dataset_hash(dataset)
                        if ds_hash not in seen_hashes and all(section in dataset for section in required_sections) and re.match(r"X7\s", dataset.splitlines()[-1].strip()):
                            datasets.append(dataset)
                            seen_hashes.add(ds_hash)
                        current_dataset = []
                        inside_dataset = False
        return datasets

    for file in glob.glob(os.path.join(directory, "**/*.[tT][xX][tT]"), recursive=True):
        if os.path.basename(file).lower() == "msg.txt":
            last_x7_line = find_last_x7_line(file)
            if last_x7_line:
                valid_datasets = extract_complete_datasets(file, last_x7_line)
                base, _ = os.path.splitext(file)
                new_file_path = f"{base}_clean.txt"
                try:
                    with open(new_file_path, "w", encoding="utf-8") as f:
                        f.write("\n\n".join(valid_datasets) if valid_datasets else "")
                    print(f"Processed {file} into {new_file_path}")
                except Exception as e:
                    print(f"Error writing {new_file_path}: {str(e)}")

def script7_merge_and_extract(directory):
    temp_path = os.path.join(directory, "temp_merged.txt")
    files_to_merge = glob.glob(os.path.join(directory, "**/msg_clean.txt"), recursive=True)
    seen_hashes = set()
    if files_to_merge:
        try:
            with open(temp_path, "w", encoding="utf-8") as f:
                for file_path in files_to_merge:
                    content = read_file(file_path)
                    if content:
                        f.write(content + "\n\n")
            print(f"Merged files into {temp_path}")
            current_dataset = []
            datasets = {}
            inside_dataset = False
            with open(temp_path, "r", encoding="utf-8", errors="ignore") as f:
                for line in f:
                    stripped_line = line.rstrip()
                    if not inside_dataset and "CRUISE PERFORMANCE REPORT" in stripped_line:
                        inside_dataset = True
                        current_dataset.append(line)
                    elif inside_dataset:
                        current_dataset.append(line)
                        if stripped_line.startswith("X7"):
                            dataset_content = "".join(current_dataset)
                            ds_hash = get_dataset_hash(dataset_content)
                            if ds_hash not in seen_hashes:
                                cc_match = re.search(r"CC\s+AP-([A-Z]{3})\b", dataset_content)
                                if cc_match:
                                    flight_code = cc_match.group(1).lower()
                                    datasets.setdefault(flight_code, []).append(dataset_content)
                                    seen_hashes.add(ds_hash)
                            current_dataset = []
                            inside_dataset = False
            for flight_code, flight_data in datasets.items():
                output_path = os.path.join(directory, f"{flight_code}.txt")
                with open(output_path, "a", encoding="utf-8") as f:
                    f.write("\n\n".join(flight_data))
                print(f"Appended data to {output_path}")
            os.remove(temp_path)
            print(f"Deleted {temp_path}")
        except Exception as e:
            print(f"Error in script7: {str(e)}")

def script8_process_flight_files(directory, month):
    def extract_complete_datasets(content, month):
        pattern = r"(.*?CRUISE PERFORMANCE REPORT.*?\n+.*?X7[^\n]*\n)"
        datasets = re.findall(pattern, content, re.DOTALL)
        required_sections = ["CC", "C0", "C1", "CE", "CN", "EC", "EE", "N1", "N2", "S1", "S2",
                             "T1", "T2", "V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8",
                             "X1", "X2", "X3", "X4", "X5", "X6", "X7"]
        valid_datasets = []
        seen_hashes = set()
        for dataset in datasets:
            if all(section in dataset for section in required_sections) and re.match(r"X7\s", dataset.splitlines()[-1].strip()):
                ds_hash = get_dataset_hash(dataset)
                if ds_hash in seen_hashes:
                    continue
                seen_hashes.add(ds_hash)
                for line in dataset.splitlines():
                    if line.startswith("CC"):
                        parts = line.split()
                        if len(parts) >= 3 and parts[2][:3].upper() == month:
                            valid_datasets.append(dataset)
                            break
        return valid_datasets

    # Keep track of the script file
    script_file = os.path.basename(__file__)
    
    # Create destination folders
    folders = {
        'A321-211': ['bmm', 'bmn', 'bmo', 'bmp', 'bmw'],
        'A320-214': ['eda', 'edg', 'edh', 'edu', 'edv'],
        'A321-251 NX': ['boe', 'bod']
    }
    for folder in folders:
        folder_path = os.path.join(directory, folder)
        os.makedirs(folder_path, exist_ok=True)

    # Process flight files for the specified month
    files_to_process = glob.glob(os.path.join(directory, "[a-zA-Z][a-zA-Z][a-zA-Z].txt"))
    for file_path in files_to_process:
        content = read_file(file_path)
        if content:
            valid_datasets = extract_complete_datasets(content, month)
            with open(file_path, "w", encoding="utf-8") as f:
                f.write("\n\n".join(valid_datasets))
            print(f"Processed {file_path} for month {month}")

    # Move XXX.txt files to appropriate folders
    for file_path in glob.glob(os.path.join(directory, "[a-zA-Z][a-zA-Z][a-zA-Z].txt")):
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

    # Delete all files except the script file and folders
    for entry in os.listdir(directory):
        entry_path = os.path.join(directory, entry)
        if os.path.isfile(entry_path) and entry != script_file:
            os.remove(entry_path)
            print(f"Deleted file: {entry_path}")
        elif os.path.isdir(entry_path) and entry not in folders:
            shutil.rmtree(entry_path)
            print(f"Deleted folder: {entry_path}")

def main():
    parent_folder = os.getcwd()
    print(f"Starting processing in: {parent_folder}")
    unzip_initial_files(parent_folder)
    script1_find_and_extract_archives(parent_folder)
    script2_convert_msg_dat_to_txt(parent_folder)
    script2_extract_report02(parent_folder)
    script3_combine_merged_reports(parent_folder)
    script4_create_master_2(parent_folder)
    script5_separate_flights_by_xxx(parent_folder)
    script6_process_msg_txt_files(parent_folder)
    script7_merge_and_extract(parent_folder)
    
    while True:
        month = input("Enter the month abbreviation (e.g., JAN/jan, MAY/may): ").strip().upper()
        if month in VALID_MONTHS:
            break
        print("Invalid month abbreviation. Please try again.")
    script8_process_flight_files(parent_folder, month)
    print("Processing complete.")

if __name__ == "__main__":
    main()