use Time::HiRes qw( time );

my @chars = ("A".."Z", "a".."z");
my %data;
my $start = time();
for( $a = 0; $a <100; $a = $a + 1 ){
    my $name;
    my $age;
    $name .= $chars[rand @chars] for 1..3;
    $age=int(rand(100));
    $data{$name} = $age;
}
my $end = time();
my $total = $end - $start;
print "Execution time: $total s\n";
