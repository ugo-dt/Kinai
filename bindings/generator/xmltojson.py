#!/usr/bin/python3

import xmltodict, json, sys, os
from pathlib import Path

def main(__input_path: str, __output_path: str):
	input = Path(__input_path)
	output = Path(__output_path)
	output.mkdir(exist_ok=True)

	for filename in os.listdir(input):
		if not filename.endswith('.xml'):
			continue
		# if not filename.startswith('class') and not filename.startswith('struct'):
		# 	continue

		input_file: Path = Path(input, filename)
		output_file: Path = Path(output, filename.removesuffix('xml') + 'json')

		with open(input_file) as xml_file:
			with open(output_file, 'w') as json_file:
				json_file.write(json.dumps(xmltodict.parse(xml_file.read()), indent=4, sort_keys=True))
				print(f'Wrote file {output_file}')

if __name__ ==  '__main__':
	if len(sys.argv) != 3:
		print('Usage: ./xmltojson.py <input_dir> <output_dir>')
		sys.exit(1)
	main(sys.argv[1], sys.argv[2])
