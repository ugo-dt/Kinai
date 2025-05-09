#!/usr/bin/python3

import json, os, sys
from pathlib import Path

from Kinako import KnClass, KnGenerator, KINAI_TYPES, KINAI_IGNORED_TYPES, KnNamespace

def main(json_dir: Path, output_path: Path):
	with open(Path(json_dir, 'namespaceKinai.json')) as kinai:
		json_data = json.load(kinai)
		for i in range(0, len(json_data['doxygen']['compounddef']['innerclass'])):
			data = json_data['doxygen']['compounddef']['innerclass'][i]

			__type: str = data['#text'].replace('Kinai::', '')
			if __type in KINAI_IGNORED_TYPES:
				continue
			KINAI_TYPES.add(__type)

	with open(Path(output_path), 'w') as output_file:
		g = KnGenerator(json_dir, output_file)
		g.write_from_file(f'{os.path.dirname(__file__)}/output/kinako_template.h')
		g.writeline('')

		for t in sorted(KINAI_TYPES):
			g.writeline(f'typedef struct Kn{t} Kn{t};')
		g.writeline('')

		with open(Path(json_dir, 'index.json')) as kinai:
			index = json.load(kinai)
			data: list[dict] = index['doxygenindex']['compound']
			
			namespaces: list[KnNamespace] = []
			classes: list[KnClass] = []

			for item in data:
				match item['@kind']:
					case 'namespace':
						namespaces.append(KnNamespace(item))
					case 'class' | 'struct':
						classes.append(KnClass(item))
					case _:
						pass

			for n in namespaces:
				g.writeline(n.__c__())
			
			for c in classes:
				g.writeline(c.__c__())

if __name__ == '__main__':
	json_dir = f'{os.path.dirname(__file__)}/output/json'
	if len(sys.argv) == 2:
		json_dir = sys.argv[1]

	output_path = f'{os.path.dirname(__file__)}/output/kinako.h'
	main(json_dir, output_path)
