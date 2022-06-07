let x = 4307466;
let y = 7371113;
let map = new ol.Map({
    target: "map",
    controls: ol.control.defaults().extend([
        new ol.control.ZoomSlider(),        //отображает полоску масштабов с указанием текущего уровня
        new ol.control.MousePosition(),     //показывает координаты текущего положения мыши
        new ol.control.OverviewMap(),       //показывает уменьшенную обзорную карту
        new ol.control.ScaleLine()          // отображает текущий масштаб
    ]),
    layers: [
        new ol.layer.Tile({
            source: new ol.source.OSM()
        })
    ],
    view: new ol.View({
        center: [x, y],
        zoom: 5,
        projection: "EPSG:3857"
    })
});

console.log(ol.style.Style);


//Добавление контролла (Градусная проекция)
let mousePositionControl = new ol.control.MousePosition( {
    // используется градусная проекция
    projection: 'EPSG:4326',
    // переопределяем функцию вывода координат
    coordinateFormat: function(coordinate) {
        // сначала широта, потом долгота и ограничиваем до 5 знаков после запятой
        return ol.coordinate.format(coordinate, '{y}, {x}', 5);
    }
});
//map.addControl(mousePositionControl);

let key = 'pk.eyJ1IjoiYWxleGFuZGVyYXVraGFkaWV2IiwiYSI6ImNsM3I0amswazBpc24zbG0xczd5MWNndHkifQ.LqoJcF5xzdk7frjW8ybk5g';

let layerPBF = new ol.layer.VectorTile({
    declutter: true,
    source: new ol.source.VectorTile({
        attributions:
            '© <a href="https://www.mapbox.com/map-feedback/">Mapbox</a> ' +
            '© <a href="https://www.openstreetmap.org/copyright">' +
            'OpenStreetMap contributors</a>',
        format: new ol.format.MVT(),
        url: 'http://localhost:3000/web50.m_r_dorogi_avtomobil_nye/{z}/{x}/{y}.pbf'

    }),
});
map.addLayer(layerPBF);

const displayFeatureInfo = function(pixel){
    const features = [];
    map.forEachFeatureAtPixel(pixel, function(feature){
        features.push(feature);
    });
    if(features.length > 0){
        const objectName = [];
        const objectCoordinates = [];
        let i, j;
        for(i = 0, j = features.length; i < j; ++i){
            objectName.push(features[i].get('style'));
            objectCoordinates.push(features[i].get("кол_во_полос"));
        }
        document.getElementById("name").innerHTML = objectName.join(', ') || '(unknown)';
        document.getElementById("coordinates").innerHTML = objectCoordinates.join(', ') || '(unknown)';
        document.getElementById("map").style.cursor = 'pointer';
    }else{
        document.getElementById("coordinates").innerHTML = '&nbsp';
        document.getElementById('name').innerHTML = '&nbsp;';
        document.getElementById("map").style.cursor = '';
    }
};

map.on('pointermove', function(evt){
    if(evt.dragging){
        return;
    }
    const pixel = map.getEventPixel(evt.originalEvent);
    displayFeatureInfo(pixel);
});

map.on('click', function (evt) {
    displayFeatureInfo(evt.pixel);
});