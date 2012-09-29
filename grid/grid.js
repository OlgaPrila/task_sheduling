$.extend({
    drag:{},
    borders:{},
    Grid:{
        it:null,
        nodes:[],
        links:[]
    },

    canvas:null,
    info: null,

    grid_init:function () {
        $('head').append('<link rel="stylesheet" type="text/css" href="./grid/grid.css">');
        this.Grid.it = $('.grid');
        this.info = $('.info-table');
        this.canvas_init();

        this.info.toggle();

        $('#addNodeBtn').click(function () {
            $.add_node();
        });

        $('#close').click(function () {
            this.info.hide();
        });

        this.borders = {
            left:this.Grid.it.offset().left,
            top:this.Grid.it.offset().top,
            right:this.Grid.it.offset().left + this.Grid.it.css('width'),
            bottom:this.Grid.it.offset().top + this.Grid.it.css('height')
        }
    },

    canvas_init:function () {
        this.canvas = document.getElementById('gCanvas');
        //TODO:change 450 on gView height. Dont know why, but it does not work right now O_o
        $('#gCanvas').attr('width', $('.gView').width()).attr('height', 750);
    },

    drawLink:function (ctx, xStart, yStart, xFinish, yFinish) {
        ctx.lineWidth = 6;
        ctx.strokeStyle = "#070";
        ctx.beginPath();
        ctx.moveTo(xStart, yStart);
        ctx.bezierCurveTo(xStart + ( xFinish - xStart) / 2, yStart,
            xFinish - ( xFinish - xStart) / 2, yFinish,
            xFinish, yFinish);
        ctx.stroke();
    },

    add_node:function () {
        var newID = $('.gView > .node').length;
        $('.gView').append('<div class="node" id="' + newID + '">' +
            '<div class="info" id="' + newID + '">i</div>' +
            '<div class="left-connector" id="' + newID + '"></div>' +
            '<div class="right-connector" id="' + newID + '"></div></div>');
        this.Grid.nodes.push({
            id:newID,
            field1:'TEXT',
            field2:Math.floor(Math.random() * 10) * newID
        });
    },

    renderLinks:function () {
        if (this.canvas.getContext) {
            var ctx = this.canvas.getContext('2d');
            ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
            var links = $.Grid.links;
            var c = ($('.left-connector').width()) / 2;
            $(links).each(function (key, lnk) {
                var xStart = lnk.fr2.offset().left + c
                , yStart = lnk.fr2.offset().top + c
                , xFinish = lnk.to2.offset().left + c
                , yFinish = lnk.to2.offset().top + c;

                $.drawLink(ctx, xStart, yStart, xFinish, yFinish);
            });
        } else {
            alert('You need Chrome, Safari or Firefox 1.5+ to work with this product.');
        }
    }
});


$(document).ready(function () {
    $.grid_init();

    $(document).mousedown(function (event) {
        var type = $(event.target).attr('class');
        switch (type) {
            case 'node':
                $.drag.node = $(event.target);
                $.drag.xDiff = event.pageX - $.drag.node.offset().left;
                $.drag.yDiff = event.pageY - $.drag.node.offset().top;
                $(document).mousemove(function (event) {
                    $.drag.node.css({left:event.pageX - $.drag.xDiff,
                                    top:event.pageY - $.drag.yDiff});
                    $.renderLinks();
                });
                $.info.hide();
                break;
            case 'right-connector':
                $(document).mouseover(function (e) {
                    var start = $(event.target);
                    var finish = $(e.target);

                    if (finish.attr('class') == 'left-connector') {
                        if (start.attr('id') != finish.attr('id')) {
                            var weight = 1;//= prompt('Set weight of the link');
                            var id = $.Grid.links.length;
                            $.Grid.links.push({
                                id:id,
                                from:start.attr('id'),
                                to:finish.attr('id'),
                                fr2:start,
                                to2:finish,
                                weight:weight
                            });
                            $(document).unbind('mouseover');
                            $.renderLinks();
                        }
                    }
                });
                break;
            case 'info':
                var evnt = $(event.target);

                if ($.info.attr('id') == evnt.attr('id')) {
                    $.info.toggle();
                } else {
                    $.info.show();
                    $.info.attr({'id':evnt.attr('id')});
                }

                $.info.css({left:evnt.offset().left + 50});
                $.info.css({top:evnt.offset().top - 30});
                $('.info-table > #field1').val($.Grid.nodes[evnt.attr('id')].field1);
                $('.info-table > #field2').val($.Grid.nodes[evnt.attr('id')].field2);
                break;
        }
    });

    $(document).mouseup(function (event) {
        var type = $(event.target).attr('class');

        $(document).unbind('mouseover');
        switch (type) {
            case 'node':
                $(document).unbind('mousemove');
                break;
            default:
            //console.log('default in mouseup');
        }
    });

});
