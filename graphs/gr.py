import matplotlib.pyplot as plt
import networkx as nx


# create a directed multi-graph
G = nx.MultiDiGraph()
f=open('graphs/gr.txt')
G.add_edges_from([tuple(map(int,x.strip().split())) for x in f])
# plot the graph
plt.figure(figsize=(8,8))
nx.draw_networkx(G)
plt.show()  # pause before exiting
f.close()
