$(document).ready(function(){
    $("#zone-1").click(function(){
        clearZones();
        activateZone(1, this);
        return false;
    });
    $("#zone-2").click(function(){
        clearZones();
        activateZone(2, this);
        return false;
    });
    $("#zone-3").click(function(){
        clearZones();
        activateZone(3, this);
        return false;
    });
    $("#zone-4").click(function(){
        clearZones();
        activateZone(4, this);
        return false;
    });
});

function clearZones(){
    $(".zone").removeClass("btn-success");
}

function activateZone(zoneNumber, el){
    $(el).addClass("btn-success");
    $.ajax("/stations.cgi?station=" + zoneNumber, {
        async: false,
        dataType:"text",
        type: "GET",
        cache: false
    });
}