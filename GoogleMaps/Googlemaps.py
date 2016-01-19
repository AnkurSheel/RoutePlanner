all_waypoints = ["Oklahoma City, Oklahoma",
                 "Boise, Idaho",
                "Wichita, Kansas", 
                "Denver, Colorado",
                "Albuquerque, New Mexico",
                "Phoenix, Arizona",
                "Las Vegas, Nevada",
                "San Francisco, California",
                "Portland, Oregon",
                "Seattle, Washington",
                "Chicago, Illinois",
                "Park City, Utah",
                "Jackson, Wyoming",
                "Billings, Montana",
                "Sioux Falls, South Dakota",
                "Omaha, Nebraska",
                "Des Moines, Iowa",
                "Minneapolis, Minnesota",
                "Milwaukee, Wisconsin",
                "Providence, Rhode Island",
                "Indianapolis, Indiana",
                "Louisville, Kentucky",y
                "Columbus, Ohio",
                "Detroit, Michigan",
                "Cleveland, Ohio",
                "Manchester, New Hampshire",
                "Portland, Maine",
                "Boston, Massachusetts",
                "Charlotte, North Carolina",
                "New Haven, Connecticut",
                "New York City, New York",
                "Ocean City, New Jersey",
                "Philadelphia, Pennsylvania",
                "Wilmington, Delaware",
                "Baltimore, Maryland",
                "Washington, D.C.",
                "Virginia Beach, Virginia",
                "Little Rock, Arkansas",
                "Charleston, South Carolina",
                "Orlando, Florida",
                "Atlanta, Georgia",
                "Nashville, Tennessee",
                "Birmingham, Alabama",
                "Jackson, Mississippi",
                "New Orleans, Louisiana",
                "Houston, Texas",
                "Oklahoma City, Oklahoma",
                "Branson, Missouri"]
        
        #all_waypoints = ["USS Alabama, Battleship Parkway, Mobile, AL",
        #         "Grand Canyon National Park, Arizona",
        #         "Toltec Mounds, Scott, AR",
        #         "San Andreas Fault, San Benito County, CA",
        #         "Cable Car Museum, 94108, 1201 Mason St, San Francisco, CA 94108",
        #         "Pikes Peak, Colorado",
        #         "The Mark Twain House & Museum, Farmington Avenue, Hartford, CT",
        #         "New Castle Historic District, Delaware",
        #         "White House, Pennsylvania Avenue Northwest, Washington, DC",
        #         "Cape Canaveral, FL",
        #         "Okefenokee Swamp Park, Okefenokee Swamp Park Road, Waycross, GA",
        #         "Craters of the Moon National Monument & Preserve, Arco, ID",
        #         "Lincoln Home National Historic Site Visitor Center, 426 South 7th Street, Springfield, IL",
        #         "West Baden Springs Hotel, West Baden Avenue, West Baden Springs, IN",
        #         "Terrace Hill, Grand Avenue, Des Moines, IA",
        #         "C. W. Parker Carousel Museum, South Esplanade Street, Leavenworth, KS",
        #         "Mammoth Cave National Park, Mammoth Cave Pkwy, Mammoth Cave, KY",
        #         "French Quarter, New Orleans, LA",
        #         "Acadia National Park, Maine",
        #         "Maryland State House, 100 State Cir, Annapolis, MD 21401",
        #         "USS Constitution, Boston, MA",
        #         "Olympia Entertainment, Woodward Avenue, Detroit, MI",
        #         "Fort Snelling, Tower Avenue, Saint Paul, MN",
        #         "Vicksburg National Military Park, Clay Street, Vicksburg, MS",
        #         "Gateway Arch, Washington Avenue, St Louis, MO",
        #         "Glacier National Park, West Glacier, MT",
        #         "Ashfall Fossil Bed, Royal, NE",
        #         "Hoover Dam, NV",
        #         "Omni Mount Washington Resort, Mount Washington Hotel Road, Bretton Woods, NH",
        #         "Congress Hall, Congress Place, Cape May, NJ 08204",
        #         "Carlsbad Caverns National Park, Carlsbad, NM",
        #         "Statue of Liberty, Liberty Island, NYC, NY",
        #         "Wright Brothers National Memorial Visitor Center, Manteo, NC",
        #         "Fort Union Trading Post National Historic Site, Williston, North Dakota 1804, ND",
        #         "Spring Grove Cemetery, Spring Grove Avenue, Cincinnati, OH",
        #         "Chickasaw National Recreation Area, 1008 W 2nd St, Sulphur, OK 73086",
        #         "Columbia River Gorge National Scenic Area, Oregon",
        #         "Liberty Bell, 6th Street, Philadelphia, PA",
        #         "The Breakers, Ochre Point Avenue, Newport, RI",
        #         "Fort Sumter National Monument, Sullivan's Island, SC",
        #         "Mount Rushmore National Memorial, South Dakota 244, Keystone, SD",
        #         "Graceland, Elvis Presley Boulevard, Memphis, TN",
        #         "The Alamo, Alamo Plaza, San Antonio, TX",
        #         "Bryce Canyon National Park, Hwy 63, Bryce, UT",
        #         "Shelburne Farms, Harbor Road, Shelburne, VT",
        #         "Mount Vernon, Fairfax County, Virginia",
        #         "Hanford Site, Benton County, WA",
        #         "Lost World Caverns, Lewisburg, WV",
        #         "Taliesin, County Road C, Spring Green, Wisconsin",
        #         "Yellowstone National Park, WY 82190"]

import googlemaps
gmaps = googlemaps.Client(key="Replace key here")

from itertools import combinations

waypoint_distances = {}
waypoint_durations = {}

for (waypoint1, waypoint2) in combinations(all_waypoints, 2):
    try:
        route = gmaps.distance_matrix(origins=[waypoint1],
                                      destinations=[waypoint2],
                                      mode="driving",
                                      language="English",
                                      units="metric")

        # "distance" is in meters
        distance = route["rows"][0]["elements"][0]["distance"]["value"]

        # "duration" is in seconds
        duration = route["rows"][0]["elements"][0]["duration"]["value"]

        waypoint_distances[frozenset([waypoint1, waypoint2])] = distance
        waypoint_durations[frozenset([waypoint1, waypoint2])] = duration
    
        print("route between %s and %s : duration %d : time %d " % (waypoint1, waypoint2, distance, duration))

    except Exception as e:
        print("Error with finding the route between %s and %s." % (waypoint1, waypoint2))

with open("my-waypoints-dist-dur.tsvb", "wb") as out_file:
    out_file.write  ("\t".join(["waypoint1",
                              "waypoint2",
                              "distance_m",
                              "duration_s"]).encode())
    
    for (waypoint1, waypoint2) in waypoint_distances.keys():
        out_file.write(b"\n" +
                       "\t".join([waypoint1,
                                  waypoint2,
                                  str(waypoint_distances[frozenset([waypoint1, waypoint2])]),
                                  str(waypoint_durations[frozenset([waypoint1, waypoint2])])]).encode())
        print("route copied %s and %s : duration %d : time %d " % (waypoint1, waypoint2, distance, duration))

with open("my-waypoints-dist-dur.csv", "w") as out_file1:
    out_file1.write  ("\t".join(["waypoint1",
                              "waypoint2",
                              "distance_m",
                              "duration_s"]))
    
    for (waypoint1, waypoint2) in waypoint_distances.keys():
        out_file1.write("\n" +
                       "\t".join([waypoint1,
                                  waypoint2,
                                  str(waypoint_distances[frozenset([waypoint1, waypoint2])]),
                                  str(waypoint_durations[frozenset([waypoint1, waypoint2])])]))


print("Hello World")