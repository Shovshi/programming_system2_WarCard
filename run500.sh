failure=false;
for i in {1..500};
 do output=$(./test1);
[[ $output == *"Status: FAILURE!"* ]] && { echo "** FAIL *";
failure=true;
 break; };
done;
$failure || echo "* Success **"