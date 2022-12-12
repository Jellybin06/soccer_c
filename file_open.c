import requests
import pandas as pd

url = 'https://fantasy.premierleague.com/api/bootstrap-static/'

r = requests.get(url)
json = r.json()
json.keys()

fpl_elements_df = pd.DataFrame(json['elements'])
fpl_elements_types_df = pd.DataFrame(json['element_types'])
fpl_teams_df = pd.DataFrame(json['teams'])

fpl_elements_df.columns

fpl_slim_elements_df = fpl_elements_df[['web_name','team'
                                        ,'element_type'
                                        ,'total_points']]
                                        
fpl_slim_elements_df['position'] = fpl_slim_elements_df.element_type.map(
    fpl_elements_types_df.set_index('id').singular_name)

fpl_slim_elements_df['team'] = fpl_slim_elements_df.team.map(
    fpl_teams_df.set_index('id').name)
    

val_list = fpl_slim_elements_df.values.tolist()

for i in range(0, 667):
  del(val_list[i][2])


print(val_list)
