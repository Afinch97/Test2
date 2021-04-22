<html>
<title>Web Page Design</title>
<head>
<script>
function q8() {
  var a = 1;
  console.log("Starting a = " + a);
  function sub1(){
      var a = 8;
      var b = 2;
      console.log(" Sub 1: a = " + a + ", b = " + b);
      
      function sub2(){
         var b = 24;
         var c = 3;
         console.log(" Sub 2: a = " + a + ", b = " + b + ", c = " + c);
         
         function sub3(){
             var c = 81;
             var d = 4;
             console.log(" Sub 3: a = " + a + ", b = " + b + ", c = " + c + ", d = " + d);
         }
         sub3();
      }
      sub2();
  }
  sub1();
}
q8();
</script>
</head>
<body>
</body>
</html>