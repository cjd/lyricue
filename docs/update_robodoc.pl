#!/usr/bin/perl
open IN, $ARGV[0];
open OUT, ">".$ARGV[0].".out";

my $text = "";
my $header = "";
my $inputs = "";
my $description = "";
my $subname = "";
my $subcontents = "";
my $oldheader = "";
while (<IN>) {
    if (/^sub /) {
        # New subroutine
        if ($subname ne "") {
            print OUT "#****f* ".$ARGV[0]."/".$subname."\n";
            print OUT "# NAME\n";
            print OUT "#   ".$subname."\n";
            print OUT "# SYNOPSIS\n";
            print OUT "#   ".$subname."(".$inputs.")\n";
            print OUT "# FUNCTION\n";
            print OUT "#   ".$description."\n";
            print OUT "# INPUTS\n";
            my @items = split(/,/, $inputs);
            foreach (@items) {
                print OUT "#   ".$_." - \n";
            }
            print OUT "# OUTPUT\n";
            print OUT "# SOURCE\n";
            print OUT "#\n";
            print OUT "sub ".$subname." {\n";
        }
        print OUT $subcontents;
        if ($subname ne "") {
            print OUT "#***\n\n";
        }
        chomp;
        $subname = $_;
        $subname =~ s/^sub (.*) .*$/$1/g;
        $oldheader = $header;
        $header = "";
        $subcontents = "";
        $inputs = "";
        $description = "";
    } elsif ((/^ *my.*\@_;$/) && ($inputs eq "")) {
        $subcontents .= $_;
        chomp;
        $inputs = $_;
        $inputs =~ s/^.*\((.*)\).*$/$1/g;
    } elsif ((/^ *debug/) && ($description eq "")) {
        $subcontents .= $_;
        chomp;
        $description = $_;
        $description =~ s/^.*debug\("(.*)".*$/$1/g;
    } else {
        $subcontents .= $_;
    }
}
        if ($subname ne "") {
            print OUT "#****f* ".$ARGV[0]."/".$subname."\n";
            print OUT "# NAME\n";
            print OUT "# SYNOPSIS\n";
            print OUT "#   ".$subname."(".$inputs.")\n";
            print OUT "# FUNCTION\n";
            print OUT "#   ".$description."\n";
            print OUT "# INPUTS\n";
            my @items = split(/,/, $inputs);
            foreach (@items) {
                print OUT "#   ".$_." - \n";
            }
            print OUT "# OUTPUT\n";
            print OUT "# SOURCE\n";
            print OUT "#\n";
            print OUT "sub ".$subname." {\n";
        }
        print OUT $subcontents;
        if ($subname ne "") {
            print OUT "#***\n\n";
        }
        chomp;
close OUT;
close IN;
