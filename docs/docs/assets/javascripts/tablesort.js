document$.subscribe(function() {
  var tables = document.querySelectorAll("article table:not([class])")
  tables.forEach(function(table) {
    // remove p from thead > tr > th
    var thead = table.getElementsByTagName('thead');
    var p = thead[0].getElementsByTagName('p');
    while(p[0])
      p[0].parentNode.innerHTML = p[0].innerHTML;

    if (table.closest('.table-no-sort')) {
      // no sorting for this
    } else {
      new Tablesort(table)
    }
  })

  // back btn @ download page
  if (window.location.href.indexOf("?src=getting_started") > -1) {
    var btn = document.getElementById("back_to_getting_started_btn");
    btn.style.display = "block";
  }
})
