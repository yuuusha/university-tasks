import csv
import json
import operator

csv_filename = "stars.csv"
json_filename = "constellations1.json"

constellations = {}

with open(csv_filename, 'r', encoding='utf-8') as csvfile:
    reader = csv.DictReader(csvfile)

    for row in reader:

        if row['constellation'] not in constellations:
            constellations[row['constellation']] = {
                'name': row['constellation'],
                'latin': row['constellation latin'],
                'abbrev': row['constellation abbrev'],
                'square': int(row['constellation square']),
                'stars': [],
                'neighbours': [neighbor.strip() for neighbor in row['constellation neighbours'].split(',')]
            }

        constellations[row['constellation']]['stars'].append({
            'name': row['star'],
            'brightness': int(row['brightness'])
        })

sorted_constellations = sorted(list(constellations.values()), key=operator.itemgetter('name', 'latin', 'abbrev', 'square'))

with open(json_filename, 'w', encoding='utf-8') as jsonfile:
    json.dump({'constellations': sorted_constellations},
              jsonfile, indent=2, ensure_ascii=False)

print(f"JSON-файл '{json_filename}' успешно создан.")
