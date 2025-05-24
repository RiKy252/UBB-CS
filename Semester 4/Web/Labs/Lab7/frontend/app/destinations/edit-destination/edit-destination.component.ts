import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { ActivatedRoute, Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { RouterModule } from '@angular/router';

@Component({
  selector: 'app-edit-destination',
  standalone: true,
  imports: [CommonModule, FormsModule, RouterModule],
  templateUrl: './edit-destination.component.html',
  styleUrls: ['./edit-destination.component.css']
})
export class EditDestinationComponent implements OnInit {
  id!: number;
  location = '';
  country = '';
  description = '';
  tourist_targets = '';
  cost_per_day: number | null = null;

  constructor(
    private route: ActivatedRoute,
    private http: HttpClient,
    public router: Router
  ) {}

  ngOnInit() {
    this.id = Number(this.route.snapshot.paramMap.get('id'));
    this.loadDestination();
  }

  loadDestination() {
    this.http.get<any>(`http://localhost/vacation_app/get_destination.php?id=${this.id}`)
      .subscribe(data => {
        this.location = data.location;
        this.country = data.country;
        this.description = data.description;
        this.tourist_targets = data.tourist_targets;
        this.cost_per_day = data.cost_per_day;
      }, err => {
        alert('Failed to load destination');
        this.router.navigate(['/']);
      });
  }

  updateDestination() {
    const payload = {
      id: this.id,
      location: this.location,
      country: this.country,
      description: this.description,
      tourist_targets: this.tourist_targets,
      cost_per_day: this.cost_per_day
    };

    this.http.post('http://localhost/vacation_app/edit_destination.php', payload)
      .subscribe({
        next: () => this.router.navigate(['/']),
        error: err => alert('Failed to update destination: ' + err.message)
      });
  }
}
