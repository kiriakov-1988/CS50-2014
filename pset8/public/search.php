<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // TODO: search database for places matching $_GET["geo"]
    
    if (empty($_GET["geo"]))
    {
        http_response_code(400);
        exit;
    }
    
    // преоброзование из адреса
    $geo = urldecode($_GET["geo"]);
    
    // print_r($geo);
    // print("\n");
    
    // $geo_lists
    $places = query("SELECT * FROM `places` 
                        WHERE (`place_name` LIKE ? OR `admin_name1` LIKE ? OR `postal_code` LIKE ?) 
                        GROUP BY place_name ORDER BY RAND(place_name) LIMIT 10", 
                        '%' . $geo . '%', '%' . $geo . '%', $geo . '%');
                                         
    
    /* foreach ($geo_lists as $geo_list)
    {
        // add place to array
        $places[] = [
            "place_name" => $geo_list["place_name"], 
            "admin_name1" => $geo_list["admin_name1"], 
            "postal_code"  => $geo_list["postal_code"], 
            "latitude"  => $geo_list["latitude"], 
            "longitude"  => $geo_list["longitude"]
        ];
    }*/
    

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
