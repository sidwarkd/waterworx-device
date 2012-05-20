$(document).ready(function(){
    $("#zone-1").click(function(){
        clearZone(4);
        clearZone(3);
        clearZone(2);
        toggleZone(1, this);
        return false;
    });
    $("#zone-2").click(function(){
        clearZone(4);
        clearZone(3);
        clearZone(1);
        toggleZone(2, this);
        return false;
    });
    $("#zone-3").click(function(){
        clearZone(4);
        clearZone(2);
        clearZone(1);
        toggleZone(3, this);
        return false;
    });
    $("#zone-4").click(function(){
        clearZone(3);
        clearZone(2);
        clearZone(1);
        toggleZone(4, this);
        return false;
    });
});

function clearZone(zoneNumber){
    var id = "#zone-" + zoneNumber;
    $(id).removeClass("btn-success");
}

function toggleZone(zoneNumber, el){
    $(el).toggleClass("btn-success");
    $.ajax("/stations.cgi?station=" + zoneNumber, {
        async: false,
        dataType:"text",
        type: "GET",
        cache: false
    });
}