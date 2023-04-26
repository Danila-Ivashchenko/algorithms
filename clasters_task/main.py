import json
import shapely
import math
import networkx as nx
import matplotlib.pyplot as plt


def get_clusters(spanning_tree: nx.Graph, n_clusters: int):
    sorted_edges = sorted(spanning_tree.edges(data=True), key=lambda x: x[2]['weight'], reverse=True)
    copy_tree = spanning_tree.copy()
    for i in range(n_clusters - 1):
        if len(sorted_edges) > i:
            copy_tree.remove_edge(*sorted_edges[i][:2])
    return list(nx.connected_components(copy_tree))


def distance(site1, site2):
    loc1, loc2 = site1["location"], site2["location"]
    phi1, phi2 = math.radians(loc1["lat"]), math.radians(loc2["lat"])
    dphi = math.radians(loc2["lat"] - loc1["lat"])
    dlambda = math.radians(loc2["lon"] - loc1["lon"])
    a = math.sin(dphi / 2) ** 2 + math.cos(phi1) * math.cos(phi2) * math.sin(dlambda / 2) ** 2
    return 6371 * 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))


def get_edges(sites, max_distance):
    edges = []
    for i, site in enumerate(sites[:-1]):
        dest = get_closest_site(site, sites[i + 1:], max_distance)
        edges.append((site["code"], dest["code"], distance(site, dest)))
    return edges


def get_closest_site(site, destinations, max_distance):
    closest_dest = None
    min_distance = 10 ** 16
    for dest in destinations:
        dist = distance(site, dest)
        if dist <= max_distance and dist < min_distance:
            closest_dest = dest
            min_distance = dist
    if closest_dest is None:
        closest_dest = destinations[-1]
    return closest_dest


def get_edges_nodes(sites, max_distance=400):
    nodes = [site["code"] for site in sites]
    edges = get_edges(sites, max_distance)
    return edges, nodes


def get_data_from_json(filename):
    with open(filename, "r") as f:
        return json.load(f)


def get_north_america_polygon() -> []:
    continents = get_data_from_json("jsonfiles/file.json")
    north_america_polygon = continents["features"][1]["geometry"]["coordinates"]
    max_area = 0
    max_polygon = []
    for i in range(len(north_america_polygon)):
        points = north_america_polygon[i][0]
        area = shapely.Polygon(points).area
        if area > max_area:
            max_area = area
            max_polygon = points
    return shapely.Polygon(max_polygon)


def get_north_america_sites(polygon, sites):
    north_america_sites = []
    for site in sites:
        p = shapely.Point((site["location"]["lon"], site["location"]["lat"]))
        if polygon.contains(p):
            north_america_sites.append(site)
    return north_america_sites


def add_cords(cords: []):
    plt.scatter(cords[0], cords[1])


def draw_map(list_of_cords: []):
    for cords in list_of_cords:
        add_cords(cords)
    plt.show()

def draw_function(list_of_sites: []):
    cords = []
    for sites in list_of_sites:
        lons = [site["location"]["lon"] for site in sites]
        lats = [site["location"]["lat"] for site in sites]
        cords += [[lons, lats]]
    draw_map(cords)

if __name__ == "__main__":
    sites = get_data_from_json("jsonfiles/base.json")

    north_america_polygon = get_north_america_polygon()
    north_america_sites = get_north_america_sites(north_america_polygon, sites)

    edges, nodes = get_edges_nodes(north_america_sites)
    graph = nx.Graph()
    graph.add_nodes_from(nodes)
    graph.add_weighted_edges_from(edges)

    num_of_forests = len(get_clusters(graph, 40))

    print("count of clusters = ", num_of_forests)
    #draw_function([sites, north_america_sites])