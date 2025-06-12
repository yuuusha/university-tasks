import csv
import json

json_filename = "constellations.json"
csv_filename = "stars.csv"

with open(json_filename, 'r', encoding='utf-8') as jsonfile:
    json_data = json.load(jsonfile)

with open(csv_filename, 'w', newline='', encoding='utf-8') as csvfile:
    fieldnames = ['star', 'brightness', 'constellation', 'constellation latin', 'constellation abbrev',
                  'constellation square', 'constellation neighbours']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

    writer.writeheader()

    stars = []

    for constellation in json_data['constellations']:
        for star in constellation['stars']:
            stars.append({
                'star': star['name'],
                'brightness': star['brightness'],
                'constellation': constellation['name'],
                'constellation latin': constellation['latin'],
                'constellation abbrev': constellation['abbrev'],
                'constellation square': constellation['square'],
                'constellation neighbours': ", ".join(constellation['neighbours'])
            })

    stars = sorted(stars, key=lambda x: x['star'])

    for star in stars:
        writer.writerow(star)

print(f"CSV-файл '{csv_filename}' успешно создан.")

