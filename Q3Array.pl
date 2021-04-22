use Time::HiRes qw( time );

my @chars = ("A".."Z", "a".."z");
my %data;
my $start = time();
for( $a = 0; $a <100; $a = $a + 1 ){
    my $name;
    my $age;
    $name .= $chars[rand @chars] for 1..3;
    $age=int(rand(100));
    $duplicate=0;
     for($i=0;$i<$a;$i++){
        if($data[$i][0]==$name){    #check if generated name exits in array or not
            $duplicate=1;   #duplicate name is found
            break;
        }
    }
    if($duplicate==0){ #if duplicate name is not found
        $data[$a][0] = $name;   #add the name to array
        $data[$a][1] = $age;    #add the age to array
    }else{ 
        $a=$a-1;
    }
}
my $end = time();
my $total = $end - $start;
print "Execution time: $total s\n";