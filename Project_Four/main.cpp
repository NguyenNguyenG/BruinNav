//
//  main.cpp
//  Project_Four
//
//  Created by nguyen nguyen on 3/8/17.
//  Copyright © 2017 nguyen nguyen. All rights reserved.
//
/*
#include "MyMap.h"
#include "provided.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{

    Navigator nav;
    nav.loadMapData("/Users/nguyennguyen/Downloads/skeleton\ 4/mapdata.txt");
    vector<NavSegment> direction;
    nav.navigate("Brentwood Country Mart", "Math Sciences", direction );
    GeoCoord hi("0","0"), bye("1","0"), n("1","0"), n2("1","1");
    GeoSegment start(hi, bye), end(n, n2);
    cout << angleBetween2Lines(start, end);
    
    return 0;
}
*/
/*
#include "provided.h"
#include <cassert>
#include <vector>
#include <string>
#include <cstdio>

void testNav(Navigator const& nav, std::string const& begin, std::string const& end) {
    std::vector<NavSegment> directions;
    fprintf(stderr, "Navigating from %s to %s: \n", begin.c_str(), end.c_str());
    NavResult nr = nav.navigate(begin, end, directions);
    fprintf(stderr, "Navigation result = %d\n", nr);
    assert(nr != NAV_BAD_SOURCE && nr != NAV_BAD_DESTINATION);
    if (nr != NAV_SUCCESS)
        printf("***** No route from %s to %s.\n", begin.c_str(), end.c_str());
    else {
        printf("***** Shortest route from %s to %s has %zu steps:\n", begin.c_str(), end.c_str(), directions.size());
        for (auto const& navseg : directions) {
            switch (navseg.m_command) {
                case NavSegment::PROCEED:
                    printf("  Proceed %s for %.6g miles along %s: from (%s,%s) to (%s,%s)\n", navseg.m_direction.c_str(),
                           navseg.m_distance, navseg.m_streetName.c_str(), navseg.m_geoSegment.start.latitudeText.c_str(),
                           navseg.m_geoSegment.start.longitudeText.c_str(), navseg.m_geoSegment.end.latitudeText.c_str(),
                           navseg.m_geoSegment.end.longitudeText.c_str());
                    break;
                case NavSegment::TURN:
                    printf("  Turn %s onto %s\n", navseg.m_direction.c_str(), navseg.m_streetName.c_str());
                    break;
            }
        }
    }
}

int main() {
    Navigator nav;
    bool r = nav.loadMapData("/Users/nguyennguyen/Downloads/skeleton/mapdata.txt");
    assert(r);
    std::vector<std::string> allAttractions{"Brentwood Country Mart",
        "Robertson Playground",
        "Thalians Mental Health Center",
        "Riviera Country Club",
        "Antietam Avenue",
        "The Annenberg Space for Photography",
        "Hyatt Regency Century Plaza",
        "2000 Avenue of the Stars",
        "Fox Plaza",
        "Twentieth Century Fox Film Corporation",
        "Century City Heliport",
        "1160 Barry Avenue",
        "1252 Barry Avenue",
        "Parking 11",
        "Easton Softball Stadium",
        "530 Bellagio Terrace",
        "Saperstein Critical Care Tower",
        "Mr. C Beverly Hills",
        "Sawtelle Veterans Chapel",
        "Veterans Hospital",
        "Jackie Robinson Stadium",
        "1 Brinkley Avenue",
        "2 Brinkley Avenue",
        "Harvard-Westlake Middle School",
        "Diddy Riese",
        "Fox Theater",
        "Mr. Noodle",
        "1031 Broxton Avenue",
        "1037 Broxton Avenue",
        "1045 Broxton Avenue",
        "1055 Broxton Avenue",
        "1061 Broxton Avenue",
        "Ami Sushi",
        "Barney's Beanery",
        "Five Guys",
        "Regent",
        "1067 Broxton Avenue",
        "1073 Broxton Avenue",
        "Ackerman Union",
        "Kerckhoff Hall",
        "Student Activities Center",
        "Ackerman Food Court",
        "Bruin Plaza",
        "John Wooden Center",
        "West Alumni Center",
        "Wooden West",
        "Pauley Pavilion",
        "Acosta Center",
        "Drake Stadium",
        "Rexford Mini Park",
        "Beverly Hills Courthouse",
        "Viceroy L'Ermitage Beverly Hills",
        "US Post Office",
        "Ryan A. Stanton, MD",
        "West Los Angeles Holiness Church",
        "Hillcrest Country Club",
        "2049 Century Park East",
        "2080 Century Park East",
        "2029 Century Park East",
        "PRHollywood",
        "Century City Shopping Mall",
        "The Playboy Mansion",
        "Mullin",
        "UCLA Lab School",
        "North Athletic Field",
        "Intramural Field",
        "Drake Stadium_2",
        "Marshall Field",
        "Covel Commons",
        "Charles E. Young Research Library",
        "Murphy Sculpture Garden",
        "University Residence",
        "Broad Art Center",
        "James Bridges Theater",
        "Melnitz Hall",
        "UCLA PVT East",
        "UCLA PVT West",
        "Life Sciences",
        "Orthopaedic Hospital Research Center",
        "Botany Building",
        "Mathias Botanical Garden",
        "Terasaki Life Science",
        "Boyer Hall",
        "Franz Hall Tower",
        "Schoenberg Music Building;Ostin Music Center;Ostin Music Center",
        "Ahmanson-Lovelace Brain Mapping Center",
        "David Geffen School of Medicine",
        "Gonda (Goldschmied) Neuroscience and Genetics Research Center",
        "MacDonald Medical Research Laboratory",
        "School of Public Health",
        "California Nanosystems Institute",
        "Neuroscience Research Building",
        "Parking 9",
        "La Kretz Hall",
        "Dickson Plaza",
        "Parking A",
        "Acacia",
        "Dykstra Hall",
        "LA Tennis Center",
        "Straus Stadium",
        "Mo Ostin Basketball Center (under construction)",
        "Environment, Health & Safety",
        "Dodd Hall",
        "Murphy Hall",
        "School of Law",
        "Wyton Drive",
        "Public Affairs",
        "Melnitz East",
        "Barrington Court",
        "Beverly Substation",
        "Beverly Hills City Hall",
        "Hotel Beverly Terrace",
        "Holmby Park",
        "Siam Chan",
        "Skylight Studios",
        "9048 Cresta Drive",
        "Cuesta Way",
        "Parking RC",
        "Spieker Aquatics Center",
        "Sunset Canyon Recreation Center",
        "Upper Picnic Area Modular Units",
        "Sunset Amphitheater",
        "Sunset Canyon Recreation Center_2",
        "Cedar",
        "De Neve Plaza",
        "Dogwood",
        "Northwest Campus Auditorium",
        "Sproul Landing",
        "Birch;De Neve Commons",
        "Evergreen",
        "Holly",
        "Saxon Basketball Court",
        "Saxon Residential Suites",
        "Ornamental Horticulture Storage Building J",
        "Ornamental Horticulture Storage Building M",
        "Parking Lot 15",
        "Saxon Residential Suites_2",
        "Hitch Residential Suites",
        "Saxon Residential Suites_3",
        "Los Angeles Temple Visitor's Center",
        "Los Angeles California Temple",
        "Pavilions 3237",
        "Veterans Administration Medical Center West Los Angeles Heliport",
        "West Pavilion",
        "East Pavilion",
        "South Pavilion",
        "BH Small Animal Hospital",
        "Beverly Hills Small Animal Hospital",
        "20th Century Fox Studios Galaxy Way",
        "InterContinental Los Angeles Century City",
        "Stage 6",
        "Bella Pita",
        "Gayley Terrace",
        "Southern Regional Library Facility",
        "Saxon Residential Suites_4",
        "Saxon Residential Suites_5",
        "Gardenia",
        "Fir",
        "Birch;De Neve Commons_2",
        "Parking DD",
        "Theta Delta Chi Fraternity",
        "Bradley International Hall",
        "Beta Theta Pi Fraternity",
        "Phi Kappa Psi Fraternity",
        "Sigma Nu Fraternity",
        "Theta Xi Fraternity",
        "Iso Fusion Café",
        "Native Foods Café",
        "Novel Cafe Westwood",
        "Gayley Center",
        "Parking 1",
        "1000 Gayley Avenue",
        "1001 Gayley Avenue",
        "1015 Gayley Avenue",
        "1019 Gayley Avenue",
        "1030 Gayley Avenue",
        "1033 Gayley Avenue",
        "1049 Gayley Avenue",
        "1050 Gayley Avenue",
        "1057 Gayley Avenue",
        "1059 Gayley Avenue",
        "1064 Gayley Avenue",
        "1065 Gayley Avenue",
        "1073 Gayley Avenue",
        "Bollywood Bites",
        "Helen's Cycles",
        "Lamonicas NY-Pizza",
        "London Cleaners",
        "Mongol BBQ",
        "O'Hara's",
        "Postal spot",
        "Thai House",
        "The Coffee Bean & Tea Leaf",
        "The Farmacy",
        "UCLA Blood & Platelet Center",
        "UCLA Extension - Westwood Village Center",
        "Westwood Copies",
        "Westwood Sporting Goods",
        "Whole Foods Market",
        "El Pollo Loco",
        "Elysee",
        "Mio Babbo's",
        "The Gayley Building",
        "Westwood Flower Garden",
        "Getty Center Car Parking Garage",
        "Getty Center Helipad",
        "Harold M. Williams Auditorium",
        "Exhibitions Pavilion",
        "Getty Conservation Institute",
        "Museum Entrance Hall",
        "North Pavilion",
        "Skylight Gardens",
        "Pierce Brothers Westwood Village Memorial Park",
        "CVS",
        "Rossiter Hall",
        "Mary Chapel",
        "Coe Memorial Library",
        "Le Montrose Suite Hotel",
        "Family Pool",
        "Hedrick Hall",
        "Hedrick Summit",
        "Park Pool",
        "Park Pool Locker Rooms",
        "UCLA Guest House",
        "W Los Angeles - Westwood",
        "Hilgard House Hotel",
        "Rage",
        "Warner Elementary School",
        "Dickson Terrace",
        "Powell Library",
        "Shapiro Fountain",
        "Pavilions 2739",
        "Pavillions",
        "10925 Kinross Avenue",
        "Bel Air Camera",
        "Headlines!",
        "Parking 36",
        "Transit Operations and Rental Services",
        "Fatburger",
        "Kinross Building North",
        "Kinross Building South",
        "Westside Family YMCA",
        "Westwood Elementary School",
        "12 La Mesa Drive",
        "510 Landfair Avenue",
        "Triangle Fraternity",
        "Alpha Epsilon Pi Fraternity",
        "W Los Angeles - West Beverly Hills",
        "UCLA Extension Administration Building",
        "Broxton Plaza",
        "Peter V. Ueberroth Building",
        "10886 Le Conte Avenue",
        "Geffen Playhouse",
        "522 Levering Avenue",
        "611 Levering Avenue",
        "679-685 Levering Avenue",
        "Plaza la Reina",
        "Red Pelican Music",
        "800 Degrees Lindbrook Drive",
        "Janss Dome",
        "Nature's Way Café",
        "Noah's Bagels",
        "SanSai Japanese Grill",
        "UCLA Extension - Lindbrook Center",
        "Veggie Grill",
        "Yogurtland",
        "Greystone Park",
        "Trustee House",
        "Parking 2",
        "Marymount Place",
        "Medical Plaza 100",
        "Resnick Neuropsychiatric Hospital",
        "Peter Morton Medical Building",
        "Medical Plaza 300",
        "564 Midvale Avenue",
        "655-667 Midvale Avenue",
        "ExtraMile",
        "708 Moreno Avenue",
        "Swim Gym",
        "Cheviot Hills Recreation Center",
        "12 Nimrod Place",
        "12 Nimrod Place",
        "Elite body sculpture",
        "NuLegal",
        "OneShotMove Moving Company",
        "Falcon Car Rental",
        "100 North Carolwood Drive",
        "Hotel Angeleno",
        "Crescent Park",
        "310 North Crescent Drive",
        "Crescent Hotel Beverly Hills",
        "Hotel Del Flores",
        "The Wallis Annenberg Center for the Performing Arts",
        "Ralph's",
        "PetCo",
        "Barbara And Marvin Davis Research Building",
        "Kenter Canyon Elementary School",
        "De Neve Square",
        "North Perugia Way",
        "Anawalt Lumber",
        "The Abbey",
        "Robert Burns Wines",
        "308 North Rodeo Drive",
        "Agent Provocateur",
        "Brunello Cucinelli",
        "Cartier",
        "Dolce & Gabbana",
        "Harry Winston",
        "Jimmy Choo",
        "Lalique",
        "Lanvin",
        "Luxe Rodeo Drive Hotel",
        "Michael Kors",
        "Moncler",
        "Patek Philippe",
        "Philipp Plein",
        "Pomellato",
        "Roberto Cavalli",
        "Rolex",
        "Stefano Ricci",
        "Tiffany & Co.",
        "Tom Ford",
        "Valentino",
        "Van Cleef & Arpels",
        "Yves Saint Laurent",
        "Brooks Brothers",
        "Chanel",
        "Giorgio Armani",
        "Hermes",
        "House of Bijan",
        "Hugo Boss",
        "Ralph Lauren",
        "Vera Wang",
        "Barbara Bui",
        "Bulgari",
        "G-Star Raw",
        "Guess",
        "La Perla",
        "Malo",
        "Stuart Weitzman",
        "Burberry",
        "Celine",
        "Coach",
        "Dior",
        "Dior Homme",
        "Gucci",
        "Louis Vuitton",
        "Miu Miu",
        "Piaget",
        "Prada",
        "Rimowa",
        "The London West Hollywood",
        "West Hollywood City Pool",
        "West Hollywood Branch County of Los Angeles Public Library",
        "Rage_2",
        "Leo Baeck Temple",
        "Jerry's Famous Deli",
        "George D. and Selma Sturges House",
        "146 North Willaman Drive",
        "Factory/Ultra Suede",
        "The Coffee Bean & Tea Leaf_2",
        "American Red Cross Los Angeles Region",
        "Sawtelle Substation",
        "Palm Lot",
        "Beverly Gardens Park",
        "Museum of Tolerance",
        "The Milky Way",
        "Bikecology",
        "JFS/SOVA Community Food & Resource Program Food Pantry",
        "Westwood Gateway Heliport",
        "Math Sciences",
        "Court of Sciences",
        "Court of Sciences Student Center",
        "Franz Hall",
        "Institute for Pure and Applied Mathematics",
        "Knudsen Hall",
        "Moore Hall",
        "Humanities Building",
        "Kinsey Teaching Pavilion",
        "Physics & Astronomy Building",
        "Haines Hall",
        "Royce Hall",
        "Bunche Hall",
        "Campbell Hall",
        "Robertson Recreation Center",
        "Rieber Terrace",
        "Rieber Vista",
        "Delta Terrace",
        "Rieber Hall",
        "Sproul Cove",
        "Rviera Country Club tennis courts",
        "2 Riviera Country Club service road",
        "Le Petit Jardin Cafe & Flowers",
        "Brockton Avenue Elementary School",
        "Bristol Farms",
        "Entrepreneurs;Korn Hall",
        "Parking 5",
        "Rolfe Hall",
        "North Campus Student Center",
        "GSEIS",
        "Hotel Angeleno_2",
        "Getty Center South Building",
        "12027 San Vicente Boulevard",
        "Chevron",
        "PZero World",
        "The Troubadour",
        "Rage_3",
        "Electric Fountain",
        "Klucid",
        "Micky's",
        "Felicia Mahood Center",
        "Cinefile Video: DVD/Blu-Ray Rental",
        "Nuart Theatre",
        "G&N Motors MBZ Certified Mercedes-Benz Service & Repair",
        "Saint Felix West Hollywood",
        "Fresh corn grill ",
        "West Hollywood Park",
        "Revolver Video Bar",
        "Juquila",
        "EagleRider",
        "Flame International",
        "West Los Angeles Finance Station Los Angeles Post Office",
        "11150 Santa Monica Boulevard",
        "MarketShare",
        "1 Santa Monica Canyon",
        "11 Santa Monica Canyon",
        "2 Santa Monica Canyon",
        "12 Santa Monica Canyon",
        "13 Santa Monica Canyon",
        "11 Santa Monica Canyon",
        "13 Santa Monica Canyon",
        "Dowlen Drive",
        "Starving Students Movers",
        "Los Angeles National Cemetery",
        "Westwood Park",
        "Jessica McIntyre, M.A., M.F.T.",
        "Equinox Fitness",
        "Equinox Fitness_2",
        "Fox Sports West",
        "Caltrans Westwood Electrical Crew Maintenance Station",
        "Horace Mann Elementary School",
        "Barrington Recreation Center",
        "Brentwood school East Campus",
        "Beverly Hills Marriott",
        "Residence Inn by Marriott Beverly Hills",
        "Beverly Hills Cosmetic Dentist Dr Joseph Goodman",
        "Prolecto Resources, Inc.",
        "Citibank",
        "Los Angeles Fire Department Fire Station 71",
        "Tenth Church of Christ, Scientist",
        "RK Law Group",
        "Cedars-Sinai Medical Center",
        "Oakhurst Park",
        "Los Angeles Fire Department Fire Station 58",
        "Proactive SEO Solutions",
        "Ruth Swissa Permanent Makeup and Skin;Bier Beisl",
        "Top Nail Spa",
        "Former Beverly Hills Post Office",
        "Jack Colker's 76",
        "Beverly Hills Fire Station 1",
        "CHS Parking",
        "Center for Health Sciences Plaza",
        "Doris Stein Eye Research Center",
        "Jules Stein Eye Institute",
        "Brain Research Institute",
        "Edie & Lew Wasserman Building",
        "Jules Stein Parking",
        "Greystone Mansion",
        "Lambda Chi Alpha Fraternity",
        "Phi Kappa Sigma Fraternity",
        "Sheats Apartments",
        "University Lutheran Chapel",
        "Zeta Beta Theta Fraternity",
        "10956 Strathmore Drive",
        "10958 Strathmore Drive",
        "10959-10963 Strathmore Drive",
        "10966 Strathmore Drive",
        "10974 Strathmore Drive",
        "10980 Strathmore Drive",
        "10984 Strathmore Drive",
        "10990 Strathmore Drive",
        "Strathmore Apartments",
        "Strathmore Apartments_2",
        "11023 Strathmore Drive",
        "11027-11037 Strathmore Drive",
        "Northwood Apartments",
        "11045 Strathmore Drive",
        "11051-11059 Strathmore Drive",
        "Strathmore Regency Apartments",
        "11089-11099 Strathmore Drive",
        "Wasserman Football Center (under construction)",
        "Luskin Conference Center",
        "Spaulding Field",
        "Luskin Conference Center_2",
        "Parking 8",
        "Facilities Management Building",
        "Campus Services Building 1",
        "Marymount High School",
        "12855 Sunset Boulevard",
        "Coldwater Canyon Park",
        "UCLA Lab School_2",
        "Cornell",
        "Sycamore Court",
        "UCLA Lab School_3",
        "Stage 9",
        "The Wilshire Thayer Heliport",
        "Factor Building",
        "Denny's",
        "UCLA School of Dentistry",
        "UCLA Health System, Teaching and Learning Center",
        "Marion Davies Children's Health Center",
        "Parking E",
        "Udine Way",
        "veteran",
        "Capital Programs",
        "Los Angeles Fire Department Fire Station 37",
        "UCLA West Medical Building",
        "Rehabilitation Building",
        "Science and Technology Research Building",
        "Parking 33",
        "714 Veteran Avenue",
        "616 Veteran Avenue",
        "archery practice field",
        "Saxon Residential Suites_6",
        "Sycamore Tennis Courts",
        "Krieger A",
        "Krieger C",
        "Krieger C;Krieger B",
        "Krieger D",
        "University of California, Los Angeles",
        "J. Paul Getty Museum",
        "Stage 5",
        "Stage 8",
        "Roxbury Park",
        "10201 West Pico Boulevard",
        "8835 West Pico Boulevard",
        "Rancho Park and Golf Course",
        "Stage 10",
        "Stage 11",
        "Stage 14",
        "Stage 15",
        "Stage 16",
        "Beverly Hills Bike Shop",
        "Los Angeles Fire Department Fire Station 92",
        "Jason Quality Welding",
        "F & S Fabrics",
        "Michael And Jeffery Restaurant",
        "Westside Pavilion",
        "Westside Pavilion_2",
        "Brentwood Country Club",
        "Los Angeles Fire Department Fire Station 19",
        "Sunset Lot",
        "The Roxy Theatre",
        "Rainbow Bar & Grill",
        "Parking 3",
        "Will Rogers Memorial Park",
        "Osteria Drago",
        "Viper Room",
        "Whisky a Go Go",
        "Night + market",
        "Westwood's Village Square",
        "Ike's Place",
        "Kaplan",
        "T-Mobile",
        "U-Mini",
        "Peet's Coffee & Tea",
        "Starbucks Coffee",
        "Subway",
        "Occidental Petroleum Heliport",
        "Chick-fil-A",
        "The Coffee Bean & Tea Leaf_3",
        "AT&T",
        "Janss Dome_2",
        "Yamato",
        "Liwan restaurant and hookah",
        "Qin West Chinese Cusine",
        "Eduardo's Border Grill",
        "Shamshiri Grill",
        "Collins",
        "Gold",
        "Kaufman Hall",
        "UCLA Anderson School of Management",
        "JD Morgan Center",
        "Engineering VI",
        "Engineering IV",
        "Ashe Student Health Center",
        "Wilson Plaza",
        "Strathmore Building",
        "UCLA Police Department",
        "Reed Neurological Research Center",
        "Semel Institute for Neuroscience and Human Behavior",
        "Learning Resource Center",
        "Neurological Rehabilitation & Research Unit",
        "Stan's Donuts",
        "Weyburn Center Building",
        "Tomodachi Sushi",
        "Parking 31",
        "Weyburn Commons",
        "The Paseo",
        "Magnolia Court",
        "Warren Hall",
        "Larry L. Hillblom Islet Research Center",
        "Sycamore Court_2",
        "Parking 32",
        "Jacaranda Court",
        "Olive Court",
        "The Maltz Park",
        "Federal Building",
        "Wadsworth Theater",
        "The Tower",
        "Westwood Medical Plaza",
        "Barney Greengrass Restaurant",
        "9355 Wilshire Boulevard",
        "9500 Wilshire Boulevard",
        "Pavilions (closed)",
        "Oppenheimer Tower",
        "Beverly Hills Plaza Hotel & Spa",
        "Helicopter Pad",
        "Los Angeles Country Club",
        "9735 Wilshire Boulevard",
        "Leif Rogers MD",
        "Snaks at Saks Fifth Avenue 5th floor",
        "Premier Business Centers",
        "Greenleaf Gourmet Chopshop",
        "Saks Fifth Avenue Men's",
        "Subway_2",
        "Capriotti's",
        "Saks Fifth Avenue",
        "Specialty Surgical Center",
        "Wilshire Motel",
        "Literati Cafe",
        "Ralphs",
        "12100 Wilshire Boulevard",
        "Wilshire Bundy Plaza",
        "Pavilions 2213",
        "Wilshire Landmark I",
        "American Bullion",
        "Layla Cafe Restaurant & Catering",
        "The Beverly Hills Litigation Group",
        "10880 Wilshire Boulevard",
        "KB Home",
        "10901 Wilshire Boulevard",
        "10929 Wilshire Boulevard",
        "Murdock Plaza",
        "Trimana",
        "UCLA Opus Project",
        "UCLA Wilshire Center",
        "10960 Wilshire Boulevard",
        "10980 Wilshire Boulevard",
        "Saint Sebastian School"};
    for (size_t i = 0; i < allAttractions.size(); ++i)
        for (size_t j = i + 1; j < allAttractions.size(); ++j) testNav(nav, allAttractions[i], allAttractions[j]);
}
*/
// This is the BruinNav main routine.  If the executable built from this file
// and the other .cpp files you write is named BruinNav (or BruinNav.exe on
// Windows), then you can run it with
//  ./BruinNav theMapDataFileName "Start Attraction" "End Attraction"
// to get the turn-by-turn instructions a user wants to see, or
//  ./BruinNav theMapDataFileName "Start Attraction" "End Attraction" -raw
// to see the sequence of NavSegments produced by Navigator::navigate()
// (Under Windows, say "BruinNav" instead of "./BruinNav")
// For example, with the mapdata.txt file we supplied you,
//  ./BruinNav mapdata.txt "Harvard-Westlake Middle School" "GreyStone Mansion"
// should produce something like
//   Routing...
//   You are starting at: Harvard-Westlake Middle School
//   Proceed 0.47 miles southeast on Brooklawn Drive
//   Turn right onto Angelo Drive
//   Proceed 0.43 miles east on Angelo Drive
//   Turn right onto Benedict Canyon Drive
//   Proceed 0.13 miles southeast on Benedict Canyon Drive
//   Turn left onto Hartford Way
//   Proceed 0.13 miles east on Hartford Way
//   Turn left onto Lexington Road
//   Proceed 0.63 miles east on Lexington Road
//   Turn right onto Alpine Drive
//   Proceed 0.07 miles southeast on Alpine Drive
//   Turn left onto West Sunset Boulevard
//   Proceed 0.20 miles northeast on West Sunset Boulevard
//   Turn left onto Mountain Drive
//   Proceed 0.15 miles northeast on Mountain Drive
//   Turn left onto Schuyler Road
//   Proceed 0.19 miles north on Schuyler Road
//   Turn right onto Stonewood Drive
//   Proceed 0.15 miles northeast on Stonewood Drive
//   You have reached your destination: GreyStone Mansion
//   Total travel distance: 2.5 miles
// and
//  ./BruinNav mapdata.txt "Harvard-Westlake Middle School" "GreyStone Mansion" -raw
// might produce 133 lines starting
//   Start: Harvard-Westlake Middle School
//   End:   GreyStone Mansion
//   34.0904161,-118.4344198 34.0905309,-118.4343340 northeast 0.0093 Brooklawn Drive
//   34.0905309,-118.4343340 34.0904815,-118.4341398 east 0.0116 Brooklawn Drive
//   34.0904815,-118.4341398 34.0903824,-118.4339467 southeast 0.0130 Brooklawn Drive
//   34.0903824,-118.4339467 34.0902310,-118.4337702 southeast 0.0145 Brooklawn Drive
//   34.0902310,-118.4337702 34.0900681,-118.4335630 southeast 0.0163 Brooklawn Drive
//   34.0900681,-118.4335630 34.0899633,-118.4334635 southeast 0.0092 Brooklawn Drive
//   34.0899633,-118.4334635 34.0897917,-118.4333739 southeast 0.0129 Brooklawn Drive
//   34.0897917,-118.4333739 34.0894654,-118.4333087 south 0.0229 Brooklawn Drive
// and ending
//   34.0904163,-118.4036377 34.0905573,-118.4036590 north 0.0098 Schuyler Road
//   34.0905573,-118.4036590 34.0908428,-118.4038080 northwest 0.0215 Schuyler Road
//   turn right Stonewood Drive
//   34.0908428,-118.4038080 34.0908832,-118.4036471 east 0.0096 Stonewood Drive
//   34.0908832,-118.4036471 34.0908732,-118.4034846 east 0.0093 Stonewood Drive
//   34.0908732,-118.4034846 34.0908807,-118.4033732 east 0.0064 Stonewood Drive
//   34.0908807,-118.4033732 34.0909505,-118.4031144 east 0.0156 Stonewood Drive
//   34.0909505,-118.4031144 34.0909630,-118.4030512 east 0.0037 Stonewood Drive
//   34.0909630,-118.4030512 34.0909256,-118.4029338 east 0.0072 Stonewood Drive
//   34.0909256,-118.4029338 34.0919749,-118.4018226 northeast 0.0964 Stonewood Drive
//
// If you build the program as is, you'll notice the turn-by-turn instructions
// say IN_SOME_DIRECTION instead of east or southwest or some actual direction.
// That's because of the template appearing a few lines below; read the comment
// before it.


#include "provided.h"
#include "support.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

// START OF WHAT YOU CAN REMOVE ONCE YOU'VE IMPLEMENTED string directionOfLine(const GeoSegment& gs)
// If you want the turn-by-turn directions to give a real direction like
// east or southwest instead of IN_SOME_DIRECTION, you'll need to
// implement the ordinary function
//    string directionOfLine(const GeoSegment& gs)
// to return a string like "east" or "southwest" based on the angle of the
// GeoSegment gs according to the table at the bottom of page 20 of the spec.
// When you do that, you can delete this comment and the template function
// below that appears here solely to allow this main.cpp to build.
// Why didn't we just write the real function for you?  Because it's also
// a function you'd find useful in producing the NavSegments in the navigate()
// method.  Since it's useful in more than one .cpp file, its declaration
// should go in support.h and its implementation in support.cpp.
/*
template<typename T>
string directionOfLine(const T& var2)
{
    double var = angleOfLine(var2);
    if(var >= 0 && var <= 22.5)
        return "east";
    else if(var > 22.5 && var <= 67.5)
        return "northeast";
    else if(var > 67.5 && var <= 112.5)
        return "north";
    else if(var > 112.5 && var <= 157.5)
        return "northwest";
    else if(var > 157.5 && var <= 202.5)
        return "west";
    else if(var> 202.5 && var <= 247.5)
        return "southwest";
    else if(var > 247.5 && var <= 292.5)
        return "south";
    else if(var > 292.5 && var <= 337.5)
        return "southeast";
    else if(var > 337.5 && var < 360)
        return "east";
    else
        return "";
}*/
// END OF WHAT YOU CAN REMOVE ONCE YOU'VE IMPLEMENTED string directionOfLine(const GeoSegment& gs)

void printDirectionsRaw(string start, string end, vector<NavSegment>& navSegments);
void printDirections(string start, string end, vector<NavSegment>& navSegments);

int main(int argc, char *argv[])
{
    bool raw = false;
    if (argc == 5  &&  strcmp(argv[4], "-raw") == 0)
    {
        raw = true;
        argc--;
    }
    if (argc != 4)
    {
        cout << "Usage: BruinNav mapdata.txt \"start attraction\" \"end attraction name\"" << endl
        << "or" << endl
        << "Usage: BruinNav mapdata.txt \"start attraction\" \"end attraction name\" -raw" << endl;
        return 1;
    }
    
    Navigator nav;
    
    if ( ! nav.loadMapData(argv[1]))
    {
        cout << "Map data file was not found or has bad format: " << argv[1] << endl;
        return 1;
    }
    
    if ( ! raw)
        cout << "Routing..." << flush;
    
    string start = argv[2];
    string end = argv[3];
    vector<NavSegment> navSegments;
    
    NavResult result = nav.navigate(start, end, navSegments);
    if ( ! raw)
        cout << endl;
    
    switch (result)
    {
        case NAV_NO_ROUTE:
            cout << "No route found between " << start << " and " << end << endl;
            break;
        case NAV_BAD_SOURCE:
            cout << "Start attraction not found: " << start << endl;
            break;
        case NAV_BAD_DESTINATION:
            cout << "End attraction not found: " << end << endl;
            break;
        case NAV_SUCCESS:
            if (raw)
                printDirectionsRaw(start, end, navSegments);
            else
                printDirections(start, end, navSegments);
            break;
    }
}

void printDirectionsRaw(string start, string end, vector<NavSegment>& navSegments)
{
    cout << "Start: " << start << endl;
    cout << "End:   " << end << endl;
    cout.setf(ios::fixed);
    cout.precision(4);
    for (auto ns : navSegments)
    {
        switch (ns.m_command)
        {
            case NavSegment::PROCEED:
                cout << ns.m_geoSegment.start.latitudeText << ","
                << ns.m_geoSegment.start.longitudeText << " "
                << ns.m_geoSegment.end.latitudeText << ","
                << ns.m_geoSegment.end.longitudeText << " "
                << ns.m_direction << " "
                << ns.m_distance << " "
                << ns.m_streetName << endl;
                break;
            case NavSegment::TURN:
                cout << "turn " << ns.m_direction << " " << ns.m_streetName << endl;
                break;
        }
    }
}

void printDirections(string start, string end, vector<NavSegment>& navSegments)
{
    cout.setf(ios::fixed);
    cout.precision(2);
    
    cout << "You are starting at: " << start << endl;
    
    double totalDistance = 0;
    string thisStreet;
    GeoSegment effectiveSegment;
    double distSinceLastTurn = 0;
    
    for (auto ns : navSegments)
    {
        switch (ns.m_command)
        {
            case NavSegment::PROCEED:
                if (thisStreet.empty())
                {
                    thisStreet = ns.m_streetName;
                    effectiveSegment.start = ns.m_geoSegment.start;
                }
                effectiveSegment.end = ns.m_geoSegment.end;
                distSinceLastTurn += ns.m_distance;
                totalDistance += ns.m_distance;
                break;
            case NavSegment::TURN:
                if (distSinceLastTurn > 0)
                {
                    cout << "Proceed " << distSinceLastTurn << " miles "
                    << directionOfLine(effectiveSegment) << " on " << thisStreet << endl;
                    thisStreet.clear();
                    distSinceLastTurn = 0;
                }
                cout << "Turn " << ns.m_direction << " onto " << ns.m_streetName << endl;
                break;
        }
    }
    
    if (distSinceLastTurn > 0)
        cout << "Proceed " << distSinceLastTurn << " miles "
        << directionOfLine(effectiveSegment) << " on " << thisStreet << endl;
    cout << "You have reached your destination: " << end << endl;
    cout.precision(1);
    cout << "Total travel distance: " << totalDistance << " miles" << endl;
}
